
// This file is part of HemeLB and is Copyright (C)
// the HemeLB team and/or their institutions, as detailed in the
// file AUTHORS. This software is provided under the terms of the
// license in the file LICENSE.

#ifndef HEMELB_LB_KERNELS_MOMENTBASIS_DHUMIERESD3Q15MRTBASIS_H
#define HEMELB_LB_KERNELS_MOMENTBASIS_DHUMIERESD3Q15MRTBASIS_H

#include "lb/lattices/D3Q15.h"
#include <array>

namespace hemelb
{
  namespace lb
  {
    namespace kernels
    {
      namespace momentBasis
      {
        /**
         *  Class implementing the Multiple Relaxation Time (MRT) moment basis presented in in d'Humieres et al. (2002)
         *  "Multiple�relaxation�time lattice Boltzmann models in three dimensions" for the D3Q15 lattice
         */
        class DHumieresD3Q15MRTBasis
        {
          public:
            /**
             * The lattice that suits this basis.
             */
            typedef lattices::D3Q15 Lattice;

            /** Moments can be separated into two groups: a) hydrodynamic (conserved) and b) ghost (non-conserved). */
            static const unsigned NUM_KINETIC_MOMENTS = 11;

            /** Matrix used to convert from the velocities space to the reduced moment space containing only kinetic moments. */
            static const double REDUCED_MOMENT_BASIS[NUM_KINETIC_MOMENTS][Lattice::NUMVECTORS];

            /** Diagonal matrix REDUCED_MOMENT_BASIS * REDUCED_MOMENT_BASIS'. See #61 for the MATLAB code used to compute it (in case REDUCED_MOMENT_BASIS is modified). */
            static const double BASIS_TIMES_BASIS_TRANSPOSED[NUM_KINETIC_MOMENTS];

            /**
             * Sets up the MRT collision matrix \hat{S}
             *
             * @param collisionMatrix MRT collision matrix, diagonal
             * @param relaxationRate LB relaxation rate used to relax some of the moments
             */
            static void SetUpCollisionMatrix(std::array<distribn_t, NUM_KINETIC_MOMENTS>& collisionMatrix, distribn_t relaxationRate);
        };
      }
    }
  }
}
#endif //HEMELB_LB_KERNELS_MOMENTBASIS_DHUMIERESD3Q15MRTBASIS_H
