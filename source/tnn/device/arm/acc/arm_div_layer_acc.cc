// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "arm_binary_layer_acc.h"

namespace TNN_NS {

DECLARE_ARM_BINARY_ACC(Div);

Status ArmDivLayerAcc::Init(Context *context, LayerParam *param, LayerResource *resource,
                            const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) {
    Status status = ArmBinaryLayerAcc::Init(context, param, resource, inputs, outputs);
    if (status != RPD_OK) {
        return status;
    }

    _Operator = [=](Float4 v1, Float4 v2, bool swap_flag) -> Float4 {
        Float4 dst = (swap_flag) ? Float4::div(v2, v1) : Float4::div(v1, v2);
        return dst;
    };

    return RPD_OK;
}

ArmDivLayerAcc::~ArmDivLayerAcc() {}

REGISTER_ARM_ACC(Div, LAYER_DIV)

}  // namespace TNN_NS