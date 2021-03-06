/*
  Copyright 2016 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATA_CONTAINER_HPP
#define DATA_CONTAINER_HPP

#include <cstddef>

namespace Opm {

    class DataContainer {
    public:
        DataContainer(size_t num_cells, size_t num_faces , size_t num_phases);

    private:
        size_t m_num_cells;
        size_t m_num_faces;
        size_t m_num_phases;
    };
}

#endif
