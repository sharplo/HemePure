
// This file is part of HemeLB and is Copyright (C)
// the HemeLB team and/or their institutions, as detailed in the
// file AUTHORS. This software is provided under the terms of the
// license in the file LICENSE.
#include "lb/iolets/InOutLetParabolicVelocity.h"
#include "configuration/SimConfig.h"

namespace hemelb
{
  namespace lb
  {
    namespace iolets
    {
      InOutLetParabolicVelocity::InOutLetParabolicVelocity() :
          maxSpeed(0.), warmUpLength(0)
      {
      }

      InOutLetParabolicVelocity::~InOutLetParabolicVelocity()
      {
      }

      InOutLet* InOutLetParabolicVelocity::Clone() const
      {
        InOutLet* copy = new InOutLetParabolicVelocity(*this);
        return copy;
      }

      LatticeVelocity InOutLetParabolicVelocity::GetVelocity(const LatticePosition& x,
                                                             const LatticeTimeStep t) const
      {
        // v(r) = vMax (1 - r**2 / a**2)
        // where r is the distance from the centreline, a is the distance from the boundary
        LatticePosition displ = x - position;
        LatticeDistance z = displ.Dot(normal);
        LatticeDistance rSq = displ.GetMagnitudeSquared() - z * z;
        Dimensionless rSqOverASq = rSq / (radius * radius);
        if (rSqOverASq > 1.0)
        {
          log::Logger::Log<log::Error, log::OnePerCore>(
            "An IOLET site with r = %lf lies outside the IOLET radius %lf.",
            std::sqrt(rSq), radius);
            std::exit(16);
        }

        // Get the max velocity
        LatticeSpeed max = maxSpeed;

        // If we're in the warm-up phase, scale down the imposed velocity
        if (t < warmUpLength)
        {
          max *= t / double(warmUpLength);
        }

        // Brackets to ensure that the scalar multiplies are done before vector * scalar.
        return normal * (max * (1. - rSqOverASq));
      }
    }
  }
}
