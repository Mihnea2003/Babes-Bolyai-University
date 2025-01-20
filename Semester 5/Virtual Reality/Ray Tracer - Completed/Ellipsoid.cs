using System;

namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color)
            : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color)
            : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // Translate the ray's origin to the ellipsoid's local space
            Vector localOrigin = (line.X0 - Center);
            localOrigin.Divide(SemiAxesLength);
            Vector localDirection = new Vector(line.Dx);
            localDirection.Divide(SemiAxesLength);

            // Calculate the quadratic equation coefficients
            double coeffA = localDirection * localDirection;
            double coeffB = 2 * (localOrigin * localDirection);
            double coeffC = (localOrigin * localOrigin) - (Radius * Radius);

            // Compute the discriminant to check for intersections
            double discriminant = coeffB * coeffB - 4 * coeffA * coeffC;

            if (discriminant < 0)
                return Intersection.NONE; // No intersection if the discriminant is negative

            // Solve the quadratic equation to find intersection distances
            double sqrtDiscriminant = Math.Sqrt(discriminant);
            double root1 = (-coeffB - sqrtDiscriminant) / (2 * coeffA);
            double root2 = (-coeffB + sqrtDiscriminant) / (2 * coeffA);

            // Ensure valid intersections within the allowed distance range
            if (root2 < minDist || root1 > maxDist)
                return Intersection.NONE;

            double validRoot = root1 >= minDist ? root1 : root2;

            // Calculate the intersection point
            Vector intersectionPoint = line.CoordinateToPosition(validRoot);

            // Compute the normal at the intersection point
            Vector normalAtPoint = (intersectionPoint - Center) / SemiAxesLength;
            normalAtPoint /= SemiAxesLength;
            normalAtPoint.Normalize();

            // Return intersection details
            return new Intersection(true, true, this, line, validRoot, normalAtPoint, Material, Color);
        }

    }
}