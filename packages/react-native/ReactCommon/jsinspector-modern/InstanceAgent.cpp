/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <jsinspector-modern/InstanceAgent.h>
#include "RuntimeTarget.h"

namespace facebook::react::jsinspector_modern {

InstanceAgent::InstanceAgent(
    FrontendChannel frontendChannel,
    InstanceTarget& target,
    SessionState& sessionState)
    : frontendChannel_(frontendChannel),
      target_(target),
      sessionState_(sessionState) {
  (void)target_;
}

bool InstanceAgent::handleRequest(const cdp::PreparsedRequest& req) {
  if (runtimeAgent_ && runtimeAgent_->handleRequest(req)) {
    return true;
  }
  return false;
}

void InstanceAgent::setCurrentRuntime(RuntimeTarget* runtimeTarget) {
  if (runtimeTarget) {
    runtimeAgent_ = runtimeTarget->createAgent(frontendChannel_, sessionState_);
  } else {
    runtimeAgent_.reset();
  }
}

} // namespace facebook::react::jsinspector_modern