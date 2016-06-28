/* **************************************************
 * File Name : LeapMotionFinger
 *
 * Date : 2016-5-28
 * **************************************************/

#include "leapmotionfinger.h"


class LeapListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    //virtual void onDisconnect(const Controller&);
    //virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    //virtual void onFocusGained(const Controller&);
    //virtual void onFocusLost(const Controller&);
    //virtual void onDeviceChange(const Controller&);
    //virtual void onServiceConnect(const Controller&);
    //virtual void onServiceDisconnect(const Controller&);
    //virtual void onServiceChange(const Controller&);
    //virtual void onDeviceFailure(const Controller&);
    //virtual void onLogMessage(const Controller&, MessageSeverity severity, int64_t timestamp, const char* msg);
};

const std::string fingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string boneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };
const float rate = 180 / PI;
void LeapListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void LeapListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
}
//
//void LeapListener::onDisconnect(const Controller& controller) {
//	// Note: not dispatched when running in a debugger.
//	std::cout << "Disconnected" << std::endl;
//}
//
//void LeapListener::onExit(const Controller& controller) {
//	std::cout << "Exited" << std::endl;
//}

void LeapListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
//    std::cout << "Frame id: " << frame.id()
//        << ", timestamp: " << frame.timestamp()
//        << ", hands: " << frame.hands().count()
//        << ", extended fingers: " << frame.fingers().extended().count() << std::endl;

    HandList hands = frame.hands();
    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
        // Get the first hand
        const Hand hand = *hl;
        std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
        //std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
        //	<< ", palm position: " << hand.palmPosition() << std::endl;
        // Get the hand's normal vector and direction
/*		const Vector normal = hand.palmNormal();
        const Vector direction = hand.direction();

        // Calculate the hand's pitch, roll, and yaw angles
        std::cout << std::string(2, ' ') << "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
            << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
            << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;

        // Get the Arm bone
        Arm arm = hand.arm();
        std::cout << std::string(2, ' ') << "Arm direction: " << arm.direction()
            << " wrist position: " << arm.wristPosition()
            << " elbow position: " << arm.elbowPosition() << std::endl;
*/
        // Get fingers
        const FingerList fingers = hand.fingers();
        // get the index finger
      /*  const FingerList indexFingerList = hand.fingers().fingerType(Finger::TYPE_INDEX);
        const Finger indexFinger = indexFingerList[0];
        const Bone metacarpalBone = indexFinger.bone(Bone::TYPE_METACARPAL);
        const Bone distalBone = indexFinger.bone(Bone::TYPE_DISTAL);

        const Vector baseDir = metacarpalBone.basis().yBasis;
        const Vector distalDir = distalBone.basis().yBasis;

        unsigned char angleData[2];
        angleData[0] = (unsigned char)(distalDir.angleTo(baseDir) * 180 / 3.1415926);*/

//        static int i = 0;
//        if (i ++ > 10)
//        {
//            mySerialPort.WriteData(angleData, 1);
//            Sleep(10);
//            i = 0;
//        }


        for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
        const Finger finger = *fl;

        const Vector baseDir = finger.bone(Bone::TYPE_METACARPAL).basis().yBasis;
        const Vector proximalDir = finger.bone(Bone::TYPE_PROXIMAL).basis().yBasis;
        const Vector distalDir = finger.bone(Bone::TYPE_DISTAL).basis().yBasis;

        uint16_t angle = (uint16_t)(rate * (distalDir.angleTo(proximalDir)+proximalDir.angleTo(baseDir)));

            if (finger.type() == Finger::TYPE_INDEX)
            {
                std::cout << std::string(4, ' ') << fingerNames[finger.type()]
                    << " finger, id: " << finger.id()
                    << ", length: " << finger.length()
                    << "mm, width: " << finger.width() << std::endl;
                // Get finger bones
                for (int b = 0; b < 4; ++b) {
                Bone::Type boneType = static_cast<Bone::Type>(b);
                Bone bone = finger.bone(boneType);
                std::cout << std::string(6, ' ') << boneNames[boneType]
                    << " bone, start: " << bone.prevJoint()
                    << ", end: " << bone.nextJoint()
                    << ", direction: " << bone.direction() << std::endl;
                }
            }
        }
    }

    if (!frame.hands().isEmpty()) {
        std::cout << std::endl;
    }

}

//void LeapListener::onFocusGained(const Controller& controller) {
//	std::cout << "Focus Gained" << std::endl;
//}
//
//void LeapListener::onFocusLost(const Controller& controller) {
//	std::cout << "Focus Lost" << std::endl;
//}
//
//void LeapListener::onDeviceChange(const Controller& controller) {
//	std::cout << "Device Changed" << std::endl;
//	const DeviceList devices = controller.devices();
//
//	for (int i = 0; i < devices.count(); ++i) {
//		std::cout << "id: " << devices[i].toString() << std::endl;
//		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
//		std::cout << "  isSmudged:" << (devices[i].isSmudged() ? "true" : "false") << std::endl;
//		std::cout << "  isLightingBad:" << (devices[i].isLightingBad() ? "true" : "false") << std::endl;
//	}
//}
//
//void LeapListener::onServiceConnect(const Controller& controller) {
//	std::cout << "Service Connected" << std::endl;
//}
//
//void LeapListener::onServiceDisconnect(const Controller& controller) {
//	std::cout << "Service Disconnected" << std::endl;
//}
//
//void LeapListener::onServiceChange(const Controller& controller) {
//	std::cout << "Service Changed" << std::endl;
//}
//
//void LeapListener::onDeviceFailure(const Controller& controller) {
//	std::cout << "Device Error" << std::endl;
//	const Leap::FailedDeviceList devices = controller.failedDevices();
//
//	for (FailedDeviceList::const_iterator dl = devices.begin(); dl != devices.end(); ++dl) {
//		const FailedDevice device = *dl;
//		std::cout << "  PNP ID:" << device.pnpId();
//		std::cout << "    Failure type:" << device.failure();
//	}
//}
//
//void LeapListener::onLogMessage(const Controller&, MessageSeverity s, int64_t t, const char* msg) {
//	switch (s) {
//	case Leap::MESSAGE_CRITICAL:
//		std::cout << "[Critical]";
//		break;
//	case Leap::MESSAGE_WARNING:
//		std::cout << "[Warning]";
//		break;
//	case Leap::MESSAGE_INFORMATION:
//		std::cout << "[Info]";
//		break;
//	case Leap::MESSAGE_UNKNOWN:
//		std::cout << "[Unknown]";
//	}
//	std::cout << "[" << t << "] ";
//	std::cout << msg << std::endl;
//}



LeapMotionFinger::LeapMotionFinger():stop(false)
{

}
/**
 * @brief LeapMotionFinger::startLeap
 * @return
 */
bool LeapMotionFinger::startLeap()
{
    LeapListener listener;
    Controller controller;


    controller.addListener(listener);

    controller.setPolicy(Leap::Controller::POLICY_ALLOW_PAUSE_RESUME);

    // Keep this process running until Enter is pressed
    std::cout << "Press Enter to quit, or enter 'p' to pause or unpause the service..." << std::endl;

    bool paused = false;
    while (true) {
        char c = std::cin.get();
        if (c == 'p') {
            paused = !paused;
            controller.setPaused(paused);
            std::cin.get(); //skip the newline
        }
        else
            break;
    }

    // Remove the sample listener when done
    controller.removeListener(listener);

        return true;
}
/**
 * @brief LeapMotionFinger::run
 */
void LeapMotionFinger::run()
{
//    LeapListener listener;
    Controller controller;
    Frame lastFrame;
    int64_t lastFrameId = 0;

//    controller.addListener(listener);

    controller.setPolicy(Leap::Controller::POLICY_ALLOW_PAUSE_RESUME);

    cout << "start run leap motion thread" << endl;

    while (true) {
        static int i = 0;
        if(stop)
        {
            cout << "leap motion thread is break" <<endl;
            break;
        }
        lastFrame = controller.frame();
        if(lastFrameId == lastFrame.id()) continue;
        lastFrameId = lastFrame.id();

        processFrame(lastFrame);
        if(i ++ > 5)
        {
            emit readyFingerAngle();
            i = 0;
        }
        usleep(50000);
    }

    // Remove the sample listener when done
//    controller.removeListener(listener);
}
/**
 * @brief LeapMotionFinger::processFrame
 * @param frame
 */
void LeapMotionFinger::processFrame(Frame frame)
{
    HandList hands = frame.hands();
    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
        // Get the first hand
        const Hand hand = *hl;
        if(!hand.isValid()) continue;
        std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
        // Get fingers
        const FingerList fingers = hand.fingers();
        const Vector handDir = hand.direction();

        int i = 0;
        for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
            const Finger finger = *fl;
            float angle;
            const Vector baseDir = finger.bone(Bone::TYPE_METACARPAL).basis().yBasis;
            const Vector proximalDir = finger.bone(Bone::TYPE_PROXIMAL).basis().yBasis;
            const Vector distalDir = finger.bone(Bone::TYPE_DISTAL).basis().yBasis;

            mFingerAngle[i].type = (char)i;
            mFingerAngle[i].valid = (finger.isValid()?'y':'n');
//            mFingerAngle[i++].angle = (uint16_t)(rate * (distalDir.angleTo(proximalDir)
                                                         /*+proximalDir.angleTo(baseDir)*/
//                                                         + proximalDir.angleTo(handDir)));
            angle = (120 - rate * proximalDir.angleTo(handDir)
                                      + rate * distalDir.angleTo(proximalDir));
            mFilter[i].addItem(angle);
            mFingerAngle[i++].angle = (uint16_t)mFilter[i].getResult();

        }
    }

}
