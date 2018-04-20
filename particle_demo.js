if ( ! Detector.webgl ) Detector.addGetWebGLMessage();

var camera, scene, renderer,
bulbLight, bulbMat, hemiLight,
object, loader, stats;
var ballMat, floorMat;


// ref for lumens: http://www.power-sure.com/lumens.htm
var bulbLuminousPowers = {
	"110000 lm (1000W)": 110000,
	"3500 lm (300W)": 3500,
	"1700 lm (100W)": 1700,
	"800 lm (60W)": 800,
	"400 lm (40W)": 400,
	"180 lm (25W)": 180,
	"20 lm (4W)": 20,
	"Off": 0
};

// ref for solar irradiances: https://en.wikipedia.org/wiki/Lux
var hemiLuminousIrradiances = {
	"3.4 lx (City Twilight)": 3.4,
	"50 lx (Living Room)": 50,
	"100 lx (Very Overcast)": 100,
	"350 lx (Office Room)": 350,
	"400 lx (Sunrise/Sunset)": 400,
	"1000 lx (Overcast)": 1000,
	"18000 lx (Daylight)": 18000,
	"50000 lx (Direct Sun)": 50000
};

var params = {
	shadows: true,
	exposure: 1,
	bulbPower: Object.keys( bulbLuminousPowers )[ 4 ],
	hemiIrradiance: Object.keys( hemiLuminousIrradiances )[0]
};


var clock = new THREE.Clock();

init();
animate();

function init() {

	var container = document.getElementById( 'container' );

	stats = new Stats();
	container.appendChild( stats.dom );


	camera = new THREE.PerspectiveCamera( 50, window.innerWidth / window.innerHeight, 0.1, 100 );
	camera.position.x = -4;
	camera.position.z = 4;
	camera.position.y = 2;

	scene = new THREE.Scene();

	var bulbGeometry = new THREE.SphereBufferGeometry( 0.02, 16, 8 );
	bulbLight = new THREE.PointLight( 0xffee88, 1, 100, 2 );

	bulbMat = new THREE.MeshStandardMaterial( {
		emissive: 0xffffee,
		emissiveIntensity: 1,
		color: 0x000000
	});
	bulbLight.add( new THREE.Mesh( bulbGeometry, bulbMat ) );
	bulbLight.position.set( 0, 2, 0 );
	bulbLight.castShadow = true;
	scene.add( bulbLight );

	hemiLight = new THREE.HemisphereLight( 0xddeeff, 0x0f0e0d, 10.0 );
	scene.add( hemiLight );

	floorMat = new THREE.MeshStandardMaterial( {
		roughness: 0.8,
		color: 0xffffff,
		metalness: 0.2,
		bumpScale: 0.0005
	});
	var textureLoader = new THREE.TextureLoader();
	textureLoader.load( "js/textures/hardwood2_diffuse.jpg", function( map ) {
		map.wrapS = THREE.RepeatWrapping;
		map.wrapT = THREE.RepeatWrapping;
		map.anisotropy = 4;
		map.repeat.set( 10, 24 );
		floorMat.map = map;
		floorMat.needsUpdate = true;
	} );
	textureLoader.load( "js/textures/hardwood2_bump.jpg", function( map ) {
		map.wrapS = THREE.RepeatWrapping;
		map.wrapT = THREE.RepeatWrapping;
		map.anisotropy = 4;
		map.repeat.set( 10, 24 );
		floorMat.bumpMap = map;
		floorMat.needsUpdate = true;
	} );
	textureLoader.load( "js/textures/hardwood2_roughness.jpg", function( map ) {
		map.wrapS = THREE.RepeatWrapping;
		map.wrapT = THREE.RepeatWrapping;
		map.anisotropy = 4;
		map.repeat.set( 10, 24 );
		floorMat.roughnessMap = map;
		floorMat.needsUpdate = true;
	} );

	ballMat = new THREE.MeshStandardMaterial( {
		color: 0x00BFFF,
		roughness: 0.5,
		metalness: 1.0
	});

	var floorGeometry = new THREE.PlaneBufferGeometry( 20, 20 );
	var floorMesh = new THREE.Mesh( floorGeometry, floorMat );
	floorMesh.receiveShadow = true;
	floorMesh.rotation.x = -Math.PI / 2.0;
	scene.add( floorMesh );

	this.external_accelerations = [new THREE.Vector3(0, -9.8 * 3, 0)];
    this.particles = []; // new Array();

    var i;
    for (i = 0; i < 10; i++) {
        var j;
        for (j = 0; j < 10; j++) {
            var k;
            for (k = 0; k < 10; k++) {
                var radius = 0.5; //TODO
                var sphereeGeo = new THREE.SphereBufferGeometry( radius, 32, 32 );
                var particle = new THREE.Mesh( sphereeGeo, ballMat );
                particle.rotation.y = Math.PI;
                particle.castShadow = false;
                particle.position.set(i * radius * 2, j * radius * 2 + 15, k * radius * 2);
                particle.lastPosition = new THREE.Vector3(i * radius * 2, j * radius * 2 + 15, k * radius * 2);
                particle.forces = new THREE.Vector3();
                particle.velocity = new THREE.Vector3(0, 0, 0);
                this.particles.push(particle);
                this.scene.add(particle);
            }
        }
        
    }


	renderer = new THREE.WebGLRenderer();
	renderer.physicallyCorrectLights = true;
	renderer.gammaInput = true;
	renderer.gammaOutput = true;
	renderer.shadowMap.enabled = true;
	renderer.toneMapping = THREE.ReinhardToneMapping;
	renderer.setPixelRatio( window.devicePixelRatio );
	renderer.setSize( window.innerWidth, window.innerHeight );
	container.appendChild( renderer.domElement );


	var controls = new THREE.OrbitControls( camera, renderer.domElement );

	window.addEventListener( 'resize', onWindowResize, false );


	var gui = new dat.GUI();

	gui.add( params, 'hemiIrradiance', Object.keys( hemiLuminousIrradiances ) );
	gui.add( params, 'bulbPower', Object.keys( bulbLuminousPowers ) );
	gui.add( params, 'exposure', 0, 1 );
	gui.add( params, 'shadows' );
	gui.open();
}

function onWindowResize() {

	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();

	renderer.setSize( window.innerWidth, window.innerHeight );

}

//

function animate() {

	requestAnimationFrame( animate );

	render();

}

var previousShadowMap = false;

function render() {
	var time = Date.now() * 0.0005;
	var delta = clock.getDelta();

	bulbLight.position.y = 10;

	renderer.render( scene, camera );

    var i;
    for (i = 0; i < this.particles.length; i++) {
        this.particles[i].forces = new THREE.Vector3(0, 0, 0);
    }

    // Apply external forces (i.e. gravity)
    for (i = 0; i < this.particles.length; i++) {
        // console.log(this.particles[i].position);
        var currParticle = this.particles[i];       
        var e;
        for (e = 0; e < this.external_accelerations.length; e++) {
            currParticle.forces.add(this.external_accelerations[e]);

            var velocity = currParticle.velocity.add(currParticle.forces.multiplyScalar(delta));
            var newPosition = currParticle.position.add(velocity.multiplyScalar(delta));

            this.particles[i].lastPosition.set(currParticle.position.x, currParticle.position.y, currParticle.position.z);//new position;
            this.particles[i].position.set(newPosition.x, newPosition.y, newPosition.z);
        }
    }

    // Build this.neighborMap.
    buildNeighborMap();

    // Enforcing incompressibility.



	renderer.toneMappingExposure = Math.pow( params.exposure, 5.0 ); // to allow for very bright scenes.
	renderer.shadowMap.enabled = params.shadows;
	bulbLight.castShadow = params.shadows;
	if( params.shadows !== previousShadowMap ) {
		ballMat.needsUpdate = true;
		floorMat.needsUpdate = true;
		previousShadowMap = params.shadows;
	}
	bulbLight.power = bulbLuminousPowers[ params.bulbPower ];
	bulbMat.emissiveIntensity = bulbLight.intensity / Math.pow( 0.02, 2.0 ); // convert from intensity to irradiance at bulb surface

	hemiLight.intensity = hemiLuminousIrradiances[ params.hemiIrradiance ];

	stats.update();

}


function hashPosition(x, y, z, radius) {
    return Math.floor((x/(2*radius) * 31 + y/(2*radius)) * 31 + z/(2*radius));
}


function buildNeighborMap() {
    this.neighborMap = {};

    var i;
    for (i = 0; i < this.particles.length; i++) {
        var currParticle = this.particles[i];
        var hashPos = hashPosition(currParticle.x, currParticle.y, currParticle.z, currParticle.radius);
        if (hashPos in this.neighborMap) {
            this.neighborMap[hashPos] = currParticle; //.push({key, value})
        } else {
            var hashParticles = [];
            hashParticles.push(currParticle);
            this.neighborMap[hashPos].push(hashParticles);
        }
    }
}

function findNeighbors(currParticle) { // need to check all surrounding cells and get hash of each 27
    // var hashPos = hashPosition(currParticle.x, currParticle.y, currParticle.z, currParticle.radius);
    var neighbors = [];
    var i;
    for (i = -1; i <= 1; i++) {
        var j;
        for (j = -1; j <= 1; j++) {
            var k;
            for (k = -1; k <= 1; k++) {
                var hashPos = hashPosition(currParticle.x + i, currParticle.y + j, currParticle.z + k, currParticle.radius);
                if (hashPos in this.neighborMap) {
                    neighbors.push(this.neighborMap[hashPos]);
                }
            }
        }
    }
    // return this.neighborMap[hashPos];
    return neighbors;
}


function findConstraintPoly6(particle, neighbor, h) {
    var total = 0;
    var rVector = particle.position.sub(neighbor.position);
    var r = Math.sqrt(Math.pow(rVector.x, 2.0) + Math.pow(rVector.y, 2.0) + Math.pow(rVector.z, 2.0));
    if (0 <= r || r <= h) {
        return 315 / (64 * Math.PI * Math.pow(h, 9.0)) * Math.pow(Math.pow(h, 2.0) - Math.pow(r, 2.0), 3.0);
    }
    return 0;
}

function findConstraintSpiky(particle, neighbor, h) {
    var total = 0;
    var rVector = particle.position.sub(neighbor.position);
    var r = Math.sqrt(Math.pow(rVector.x, 2.0) + Math.pow(rVector.y, 2.0) + Math.pow(rVector.z, 2.0));
    if (0 <= r || r <= h) {
        return 15 / (Math.PI * Math.pow(h, 6.0)) * Math.pow(h - r, 3.0);
    }
    return 0;
}

function findGradient(particle, neighbors, h, p0) { // might need neighbor and non-neighbor cases
    var total = 0;
    var j;
    for (j = 0; j < neighbors.length; j++) {
        total += findConstraintSpiky(particle, neighbors[j], h);
    }

    // if (p0 != 0) {
    //     return total / p0;
    // }
    return total / p0;
}

function findLambda(particle, neighbors, h, p0, epsilon) {
    var Ci = 0;
    var j;
    for (j = 0; j < neighbors.length; j++) {
        Ci += findConstraintPoly6(particle, neighbors[j], h);
    }
    Ci = Ci / p0 - 1.0;

    var gradient = epsilon;
    var k;
    for (k = 0; k < this.particles.length; k++) { // TODO: should this be neighbors only, if not then, we need 2 cases in gradient
        gradient += findGradient(this.particles[k], findNeighbors(this.particles[k]), h, p0);
    }

    return -Ci / Math.pow(Math.abs(gradient), 2.0);
}



