// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban, Justin Madsen
// =============================================================================
//
// HMMWV wheel subsystem
//
// =============================================================================

#include <algorithm>

#include "chrono_vehicle/ChVehicleModelData.h"
#include "chrono_models/vehicle/hmmwv/HMMWV_Wheel.h"
#include "chrono_thirdparty/filesystem/path.h"

namespace chrono {
namespace vehicle {
namespace hmmwv {

// -----------------------------------------------------------------------------
// Static variables
// -----------------------------------------------------------------------------

const double HMMWV_Wheel::m_mass = 18.8;
const ChVector<> HMMWV_Wheel::m_inertia(0.4634, 0.6243, 0.4634);

const double HMMWV_Wheel::m_radius = 0.268;
const double HMMWV_Wheel::m_width = 0.22;

// -----------------------------------------------------------------------------

HMMWV_Wheel::HMMWV_Wheel(const std::string& name) : ChWheel(name) {
    m_vis_mesh_file = "hmmwv/hmmwv_rim.obj";
}

void HMMWV_Wheel::Initialize(std::shared_ptr<ChBody> spindle,
  VehicleSide side,
  double offset
) {
    ChWheel::Initialize(spindle, side, offset);

    ChContactMaterialData mat_info;
    auto material = mat_info.CreateMaterial(spindle->GetSystem()->GetContactMethod());
    spindle->GetCollisionModel()->ClearModel();
    spindle->GetCollisionModel()->AddCylinder(material, m_radius, m_radius, m_width / 2, ChVector<>(0, m_offset, 0));
    spindle->GetCollisionModel()->BuildModel();
}

}  // end namespace hmmwv
}  // end namespace vehicle
}  // end namespace chrono
