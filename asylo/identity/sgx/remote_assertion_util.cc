/*
 *
 * Copyright 2018 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "asylo/identity/sgx/remote_assertion_util.h"

#include "absl/strings/str_cat.h"

namespace asylo {
namespace sgx {
namespace {

constexpr char kRemoteAssertionVersion[] = "Asylo SGX Remote Assertion v1";

}  // namespace

Status MakeRemoteAssertion(const std::string &user_data,
                           const CodeIdentity &identity,
                           const SigningKey &signing_key,
                           const std::vector<CertificateChain> &cert_chains,
                           RemoteAssertion *assertion) {
  assertion->Clear();
  assertion->set_signature_scheme(signing_key.GetSignatureScheme());
  for (const auto &chain : cert_chains) {
    *assertion->add_certificate_chains() = chain;
  }

  RemoteAssertionPayload payload;
  payload.set_version(kRemoteAssertionVersion);
  payload.set_signature_scheme(signing_key.GetSignatureScheme());
  payload.set_user_data(user_data);
  *payload.mutable_identity() = identity;

  if (!payload.SerializeToString(assertion->mutable_payload())) {
    return Status(error::GoogleError::INTERNAL, "Serialization failed");
  }

  std::vector<uint8_t> signature;
  Status status = signing_key.Sign(assertion->payload(), &signature);
  if (!status.ok()) {
    return status;
  }
  assertion->set_signature(reinterpret_cast<const char *>(signature.data()),
                           signature.size());

  return Status::OkStatus();
}

Status VerifyRemoteAssertion(const std::string &user_data,
                             const VerifyingKey &verifying_key,
                             const std::vector<Certificate> &root_certificates,
                             const RemoteAssertion &assertion,
                             CodeIdentity *identity) {
  return Status(error::GoogleError::UNIMPLEMENTED, "Not implemented");
}

}  // namespace sgx
}  // namespace asylo
