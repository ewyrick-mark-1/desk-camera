# Desk Lamp Mounted Camera with Rolling Camera Buffer

#WIP!!
## Overivew

This project aims to create a simple and effective way to passivly record and store a video feed of a workspace. This is intended to allow for one to stay "in the flow", not worrying about visual documentation, while allowing retreval later.

By tying this to a desk lamp, this provides a convenient setup, as desk lamps typically already point at the work space. This also solves any concrens surrounding poor lighting, as the lamp itself can light up the workspace.

## Scope

This project's scope can be broken into these milestones:

- 1. MVP - get a USB webcam ziptied to a desk lamp and get the buffer working.
- 2. Establish a local web UI for monitoring and easy acces to the video feed.
- 3. Design and build a more integrated solution. Move away from the zip tie solution, and towards a custom lamp head.
- 4. introduce multiple cameras for stereo+ perspectives.
- 5. use multiple perspectives to establish multi-viewpoint 3D reconstruction of the workspace.
- 6. introduce slam tracking for accurate positional tracing of the lamp head to account for movements. A basic IMU could likely do this fine as well.

This project is designed to start shallow, and allow for deeper expansion as time goes on.

## Hardware

Current available hardware is a rasberry pi 4b 4gb. This will suffice for 1 - 4, but may require an upgrade beyond those steps.

## Software

This project will be mostly in Cpp - maybe some C. I want to keep it decently close to the metal, with a reasonable ammount of abstraction. C would introduce a lot of complexity and risk surface for marginal gains.
