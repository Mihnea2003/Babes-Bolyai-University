using System;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist, bool skip = false)
        {
            var intersection = Intersection.NONE;

            foreach (var geometry in geometries)
            {
                if (skip && geometry is RawCtMask) continue;
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }

        private bool IsLit(Vector point, Light light)
        {
            var line = new Line(light.Position, point);
            var intersection = FindFirstIntersection(line, 0.001, (light.Position - point).Length(), true);
            if (!intersection.Valid || !intersection.Visible)
                return true;
            return intersection.T > (light.Position - point).Length() - 0.001;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var backgroundColor = new Color(0.2, 0.2, 0.2, 1.0); // Default background color
            var image = new Image(width, height);

            for (var x = 0; x < width; x++)
            {
                for (var y = 0; y < height; y++)
                {
                    double u = ImageToViewPlane(x, width, camera.ViewPlaneWidth);
                    double v = ImageToViewPlane(y, height, camera.ViewPlaneHeight);

                    Vector T = (camera.Up ^ camera.Direction).Normalize(); // Right vector of the view plane
                    Vector V = (camera.Direction * camera.ViewPlaneDistance + T * u + camera.Up * v).Normalize();

                    Line ray = new Line(camera.Position, V + camera.Position); // Ray from camera to pixel
                    Intersection intersection = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                    if (intersection.Valid && intersection.Visible)
                    {
                        var color = new Color();

                        foreach (var light in lights)
                        {
                            var L = intersection.Material.Ambient * light.Ambient; // Ambient light

                            if (IsLit(intersection.Position, light))
                            {
                                Vector C = light.Position; // Light position
                                Vector E = camera.Position; // Camera position
                                Vector D = intersection.Position; // Intersection point

                                Vector G = (C - D).Normalize(); // Vector from intersection to light
                                Vector N = intersection.Normal; // Normal at intersection point
                                double NdotT = N * G; // Dot product of N and G

                                if (NdotT > 0)
                                {
                                    L += intersection.Material.Diffuse * light.Diffuse * NdotT; // Diffuse component
                                }

                                Vector R = (N * (2 * NdotT) - G).Normalize(); // Reflection vector
                                Vector E_dir = (E - D).Normalize(); // Vector from intersection to camera
                                double EdotR = E_dir * R; // Dot product of E and R

                                if (EdotR > 0)
                                {
                                    L += intersection.Material.Specular * light.Specular *
                                         Math.Pow(EdotR, intersection.Material.Shininess); // Specular component
                                }

                                L *= light.Intensity;
                            }

                            color += L;
                        }

                        image.SetPixel(x, y, color);
                    }
                    else
                    {
                        image.SetPixel(x, y, backgroundColor); // Set background color
                    }
                }
            }

            image.Store(filename);
        }

    }
}