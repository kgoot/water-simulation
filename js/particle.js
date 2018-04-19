// expand THREE.js Sphere to support collision tests versus Box3
// we are creating a vector outside the method scope to avoid spawning a new
// instance of Vector3 in every check
THREE.Sphere.__closest = new THREE.Vector3();
THREE.Sphere.prototype.intersectsBox = function (box) {
    // get box closest point to sphere center by clamping
    THREE.Sphere.__closest.set(this.center.x, this.center.y, this.center.z);
    THREE.Sphere.__closest.clamp(box.min, box.max);

    var distance =  this.center.distanceToSquared(THREE.Sphere.__closest);
    return distance < (this.radius * this.radius);
};

Game.init = function () {
    this.debug = false;
    this.external_accelerations = [new THREE.Vector3(0, -9.8*3, 0)];
    this.particles = []; // new Array();

    var i;
    for (i = 0; i < 3; i++) {
        var j;
        for (j = 0; j < 3; j++) {
            var k;
            for (k = 0; k < 3; k++) {
                var particle = new THREE.Mesh(
                    new THREE.SphereGeometry(0.2), this.materials.solid);
                particle.position.set(i, j + 15, k );
                particle.lastPosition = new THREE.Vector3(i, j + 15, k);
                particle.forces = new THREE.Vector3();
                particle.velocity = new THREE.Vector3(0, 0, 0);
                this.particles.push(particle);
                this.scene.add(particle);
            }
        }
        
    }

    this.controls = new THREE.TransformControls(
        this.camera, this.renderer.domElement);
    this.controls.space = 'world';
    this.scene.add(this.controls);

    this.timestamp = 0;
};

Game.update = function (delta) {
    this.timestamp += delta;
    console.log(delta);

    this.controls.update();

    var i;
    for (i = 0; i < this.particles.length; i++) {
        this.particles[i].forces = new THREE.Vector3(0, 0, 0);
    }
    
    console.log("hello world");
    for (i = 0; i < this.particles.length; i++) {
        console.log(this.particles[i].position);
        var currParticle = this.particles[i];       
        var e;
        for (e = 0; e < this.external_accelerations.length; e++) {
            this.particles[i].forces.add(this.external_accelerations[e]);

            var velocity = this.particles[i].velocity.add(this.particles[i].forces.multiplyScalar(delta));
            var newPosition = this.particles[i].position.add(velocity.multiplyScalar(delta));

            this.particles[i].lastPosition.set(this.particles[i].position.x, this.particles[i].position.y, this.particles[i].position.z);//new position;
            this.particles[i].position.set(newPosition.x, newPosition.y, newPosition.z);
        }
    }

    // rotate the knot
    // this.knot.rotation.x += (Math.PI / 4) * delta;
    // this.knotBBox.setFromObject(this.knot); // re-calculate AABB

    // change sphere size
    // var scale = 0.25 + Math.abs(Math.sin(this.timestamp));
    // this.sphere.scale.set(scale, scale, scale);
    // re-calculate bounding sphere
    // this.sphereBBox.radius = this.sphere.geometry.boundingSphere.radius * scale;
    // update shadow size
    // Utils.updateShadow(this.sphereShadow, this.sphere);

    // update the ball AABB position and shadow
    // this.ballBBox.center.set(
    //     this.ball.position.x, this.ball.position.y, this.ball.position.z);
    // Utils.updateShadow(this.ballShadow, this.ball);

    // this.sphere.material =
    //     this.sphereBBox.intersectsSphere(this.ballBBox)
    //     ? this.materials.colliding
    //     : this.materials.solid;

    // this.knot.material = this.ballBBox.intersectsBox(this.knotBBox)
    //     ? this.materials.colliding
    //     : this.materials.solid;
};
