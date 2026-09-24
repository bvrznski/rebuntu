# events

Events subsystem — Event, Signal, Request, Response types and Channel implementations.

This subsystem implements Rebuntu's communication grammar independently of transport
mechanism. Types are transport-agnostic; implementations may use in-process calls,
file descriptors, Unix sockets, or D-Bus as appropriate.

Architecture:
  - Event: immutable statement that something occurred (e.g., device plugged in)
  - Request: semantic ask for action (e.g., "start service X")
  - Response: reply to a Request
  - Message: transport-neutral envelope carrying typed payload
  - Signal: lightweight control indication (pause/resume/cancel)

Types are defined in src/runtime/contracts.hpp and src/system/runtime/contracts.hpp.
This subsystem provides:
  - Channel interface for sending/receiving messages
  - In-memory channel implementation (for in-process use)
  - Backpressure policies for bounded queues

Status: IMPLEMENTING — Phase 0.15 communication grammar proof of concept.