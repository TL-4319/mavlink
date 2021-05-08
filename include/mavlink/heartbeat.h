/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef INCLUDE_MAVLINK_HEARTBEAT_H_
#define INCLUDE_MAVLINK_HEARTBEAT_H_

#include "core/core.h"
#include "global_defs/global_defs.h"
#include "./mavlink_types.h"
#include "common/mavlink.h"

namespace bfs {

class MavLinkHeartbeat {
 public:
  /* Config */
  inline void hardware_serial(HardwareSerial *bus) {bus_ = bus;}
  inline void aircraft_type(const AircraftType type) {aircraft_type_ = type;}
  inline void sys_id(const uint8_t sys_id) {sys_id_ = sys_id;}
  /* Aircraft type, system and component ID getters */
  inline constexpr AircraftType aircraft_type() const {return aircraft_type_;}
  inline constexpr uint8_t sys_id() const {return sys_id_;}
  inline constexpr uint8_t comp_id() const {return comp_id_;}
  /* 
  * Setters for the throttle enabled flag, aircraft mode, and aircraft state
  */
  inline void throttle_enabled(const bool val) {throttle_enabled_ = val;}
  inline void aircraft_mode(const AircraftMode val) {aircraft_mode_ = val;}
  inline void aircraft_state(const AircraftState val) {aircraft_state_ = val;}
  /* Update method */
  void Update();

 private:
  /* Serial bus */
  HardwareSerial *bus_;
  /* Config */
  uint8_t sys_id_ = 1;
  AircraftType aircraft_type_;
  static constexpr uint8_t comp_id_ = MAV_COMP_ID_AUTOPILOT1;
  static constexpr uint8_t autopilot_ = MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY;
  /* Message buffer */
  mavlink_message_t msg_;
  uint16_t msg_len_;
  uint8_t msg_buf_[MAVLINK_MAX_PACKET_LEN];
  /* Data */
  bool throttle_enabled_ = false;
  AircraftMode aircraft_mode_ = AircraftMode::MANUAL;
  AircraftState aircraft_state_ = AircraftState::INIT;
  /* Timing */
  static constexpr uint16_t HEARTBEAT_PERIOD_MS_ = 1000;
  elapsedMillis heartbeat_timer_ms_;
  /* Heartbeat */
  void SendHeartbeat();
  /* Heartbeat variables */
  static constexpr uint32_t custom_mode_ = 0;
  uint8_t type_;
  uint8_t mode_;
  uint8_t state_;
};

}  // namespace bfs

#endif  // INCLUDE_MAVLINK_HEARTBEAT_H_
