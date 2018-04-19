// THREE.Sphere.__closest = new THREE.Vector3();
// THREE.Sphere.prototype.intersectsBox = function (box) {
// // get box closest point to sphere center by clamping
// THREE.Sphere.__closest.set(this.center.x, this.center.y, this.center.z);
// THREE.Sphere.__closest.clamp(box.min, box.max);

// var distance =  this.center.distanceToSquared(THREE.Sphere.__closest);
// return distance < (this.radius * this.radius);
// };

Game.init = function () {
    this.debug = false;

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

    hemiLight = new THREE.HemisphereLight( 0xddeeff, 0x0f0e0d, 0.02 );
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
        color: 0xffffff,
        roughness: 0.5,
        metalness: 1.0
    });
    textureLoader.load( "js/textures/planets/earth_atmos_2048.jpg", function( map ) {
        map.anisotropy = 4;
        ballMat.map = map;
        ballMat.needsUpdate = true;
    } );
    textureLoader.load( "js/textures/planets/earth_specular_2048.jpg", function( map ) {
        map.anisotropy = 4;
        ballMat.metalnessMap = map;
        ballMat.needsUpdate = true;
    } );

    var floorGeometry = new THREE.PlaneBufferGeometry( 20, 20 );
    var floorMesh = new THREE.Mesh( floorGeometry, floorMat );
    floorMesh.receiveShadow = true;
    floorMesh.rotation.x = -Math.PI / 2.0;
    scene.add( floorMesh );

    var ballGeometry = new THREE.SphereBufferGeometry( 0.05, 32, 32 );
    var ballMesh = new THREE.Mesh( ballGeometry, ballMat );
    ballMesh.position.set( 1, 0.5, 1 );
    ballMesh.rotation.y = Math.PI;
    ballMesh.castShadow = true;
    scene.add( ballMesh );

    var i;
    for (i = 0; i < 3; i++) {
        var j;
        for (j = 0; j < 3; j++) {
            var k;
            for (k = 0; k < 3; k++) {
                var sphereeGeo = new THREE.SphereBufferGeometry( 0.05, 32, 32 );
                var sphereeMesh = new THREE.Mesh( sphereeGeo, ballMat );
                sphereeMesh.position.set( i, j, k );
                sphereeMesh.rotation.y = Math.PI;
                sphereeMesh.castShadow = true;
                this.scene.add(sphereeMesh);
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
};

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
    var time = Date.now() * 0.0005;
    var delta = clock.getDelta();

    bulbLight.position.y =  0.75 + 1.25;

    renderer.render( scene, camera );

    stats.update();

}
