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

	drawLight();
	drawBoundingBox();

	this.external_accelerations = [new THREE.Vector3(0, -9.8*3, 0)];
    this.particles = []; // new Array();

    var i;
    for (i = 0; i < 3; i++) {
        var j;
        for (j = 0; j < 3; j++) {
            var k;
            for (k = 0; k < 3; k++) {
                var sphereeGeo = new THREE.SphereBufferGeometry( 0.05, 32, 32 );
                var particle = new THREE.Mesh( sphereeGeo, ballMat );
                particle.rotation.y = Math.PI;
                particle.castShadow = false;
                particle.position.set(i, j + 15, k);
                particle.lastPosition = new THREE.Vector3(i, j + 15, k);
                particle.forces = new THREE.Vector3();
                particle.predPosition = new THREE.Vector3();
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

function drawLight() {
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

	hemiLight = new THREE.HemisphereLight( 0xddeeff, 0x0f0e0d, 0.02 );
	scene.add( hemiLight );
}

function drawBoundingBox() {
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

	var planeGeometry = new THREE.PlaneBufferGeometry( 20, 20 );
	var planeMaterial = new THREE.MeshBasicMaterial( {color: 0xffff00, side: THREE.DoubleSide, transparent: true, opacity: 0.3} );
	var bottomPlane = new THREE.Mesh(planeGeometry, planeMaterial);
	bottomPlane.rotation.x = -Math.PI / 2.0;
	scene.add(bottomPlane);

	var backPlane = new THREE.Mesh(planeGeometry, planeMaterial);
	backPlane.rotation.y = -Math.PI / 2.0;
	backPlane.translateY(10);
	backPlane.translateZ(-10);
	scene.add(backPlane);

	var frontPlane = new THREE.Mesh(planeGeometry, planeMaterial);
	frontPlane.rotation.y = -Math.PI / 2.0;
	frontPlane.translateY(10);
	frontPlane.translateZ(10);
	scene.add(frontPlane);

	var rightPlane = new THREE.Mesh(planeGeometry, planeMaterial);
	rightPlane.translateY(10);
	rightPlane.translateZ(-10);
	scene.add(rightPlane);

	var leftPlane = new THREE.Mesh(planeGeometry, planeMaterial);
	leftPlane.translateY(10);
	leftPlane.translateZ(10);
	scene.add(leftPlane);
}

function onWindowResize() {

	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();

	renderer.setSize( window.innerWidth, window.innerHeight );

}


function animate() {

	requestAnimationFrame( animate );

	render();

}

var previousShadowMap = false;

function render() {
	var time = Date.now() * 0.0005;
	var delta = clock.getDelta();

	bulbLight.position.y = 0.75 + 1.25;

	renderer.render( scene, camera );

    var i;
    for (i = 0; i < this.particles.length; i++) {
        this.particles[i].forces = new THREE.Vector3(0, 0, 0);
    }

    for (i = 0; i < this.particles.length; i++) {
        var currParticle = this.particles[i];       
        var e;
        for (e = 0; e < this.external_accelerations.length; e++) {
            this.particles[i].forces.add(this.external_accelerations[e]);

            var velocity = this.particles[i].velocity.add(this.particles[i].forces.multiplyScalar(delta));
            var newPosition = this.particles[i].position.add(velocity.multiplyScalar(delta));

            this.particles[i].lastPosition.set(this.particles[i].position.x, this.particles[i].position.y, this.particles[i].position.z);//new position;
            this.particles[i].position.set(newPosition.x, newPosition.y, newPosition.z);
            this.particles[i].predPosition.set(newPosition.x, newPosition.y, newPosition.z);
        }
    }

	renderer.toneMappingExposure = Math.pow( params.exposure, 5.0 ); // to allow for very bright scenes.
	renderer.shadowMap.enabled = params.shadows;
	bulbLight.castShadow = params.shadows;
	if( params.shadows !== previousShadowMap ) {
		ballMat.needsUpdate = true;
		previousShadowMap = params.shadows;
	}
	bulbLight.power = bulbLuminousPowers[ params.bulbPower ];
	bulbMat.emissiveIntensity = bulbLight.intensity / Math.pow( 0.02, 2.0 ); // convert from intensity to irradiance at bulb surface

	hemiLight.intensity = hemiLuminousIrradiances[ params.hemiIrradiance ];

	stats.update();

}