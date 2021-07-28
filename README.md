# pathtracer
A simple pathtracer for spherical objects

Pseudo-code from Wikipedia :

  Color TracePath(Ray ray, count depth) {
    if (depth >= MaxDepth) {
      return Black;  // Bounced enough times.
    }

    ray.FindNearestObject();
    if (ray.hitSomething == false) {
      return Black;  // Nothing was hit.
    }

    Material material = ray.thingHit->material;
    Color emittance = material.emittance;

    // Pick a random direction from here and keep going.
    Ray newRay;
    newRay.origin = ray.pointWhereObjWasHit;

    // This is NOT a cosine-weighted distribution!
    newRay.direction = RandomUnitVectorInHemisphereOf(ray.normalWhereObjWasHit);

    // Probability of the newRay
    const float p = 1 / (2 * PI);

    // Compute the BRDF for this ray (assuming Lambertian reflection)
    float cos_theta = DotProduct(newRay.direction, ray.normalWhereObjWasHit);
    Color BRDF = material.reflectance / PI;

    // Recursively trace reflected light sources.
    Color incoming = TracePath(newRay, depth + 1);

    // Apply the Rendering Equation here.
    return emittance + (BRDF * incoming * cos_theta / p);
  }

  void Render(Image finalImage, count numSamples) {
    foreach (pixel in finalImage) {
      foreach (i in numSamples) {
        Ray r = camera.generateRay(pixel);
        pixel.color += TracePath(r, 0);
      }
      pixel.color /= numSamples;  // Average samples.
    }
  }
