#ifndef CAMERA_MARLIN_H
#define CAMERA_MARLIN_H 1

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#include <dc1394/dc1394.h>
#include <dc1394/register.h>

#include "camera1394.h"
#include "frame.h"

namespace camera
{

#ifndef DC1394_ERR_THROW
#define DC1394_ERR_THROW(err,message)                     \
  do {                                                    \
    if (err!=DC1394_SUCCESS) {                            \
      std::stringstream ss;                               \
      ss << dc1394_error_get_string(err) << ": "          \
         << __FUNCTION__ << " (" << __FILE__ << ", line " \
         << __LINE__ << "): " << message;                 \
      throw(CameraException(ss.str()));                   \
    }                                                     \
  } while (0);
#endif /* DC1394_ERR_THROW */

#ifndef DC1394_ERR_OUT
#define DC1394_ERR_OUT(err,message)                     \
  if (err!=DC1394_SUCCESS) {                            \
    std::cerr << dc1394_error_get_string(err) << ": "   \
       << __FUNCTION__ << " (" << __FILE__ << ", line " \
       << __LINE__ << "): " << message << std::endl;    \
  }
#endif /* DC1394_ERR_OUT */


    class Marlin : public Camera1394
    {
        public:
            /**
             * Setect the camera (let dc1394 enumerate the cameras on the bus)
             * @param index Marlin to use [0..avail-1]
             */
            Marlin(uint32_t index = 0);

            /**
             * Set the region of interest (for format7 only)
             * @param roi a structure the defined x and y offsets and the width and height
             * of the region
             */
            void setROI(const camera_roi_t &roi) throw(CameraException) { this->roi = roi; }

            void resetInternal() throw(CameraException);

            //***
            //*** Marlin specific API follows
            //***

            void enableHDR(bool value, uint32_t knee1 = 0, uint32_t knee2 = 0);
            bool isHDR();

            void printFeatures();

            struct version_t
            {
                uint32_t uctype;
                uint32_t version;
                uint32_t camera_id;
                uint32_t fpga_version;
            };

            version_t getVersion();

            void opAutoWhiteBalance();

            struct white_balance_t {
                uint32_t bu;
                uint32_t rv;
            };

            void setWhiteBalance(const white_balance_t wb);
            white_balance_t getWhiteBalance();

            void setBrightness(unsigned char value);
            unsigned char getBrightness();

            void setExposure(unsigned char value);
            unsigned char getExposure();

            void enableGamma(bool value);
            bool isGamma();

            void setGamma(unsigned char value);
            unsigned char getGamma();

            void setShutter(unsigned short value);
            unsigned short getShutter();

            void enableAutoShutter(bool value);
            void enableAutoShutter(bool value, uint32_t min, uint32_t max);
            bool isAutoShutter();

            void setGain(unsigned char value);
            unsigned char getGain();

            void enableAutoGain(bool value);
            void enableAutoGain(bool value, uint32_t min, uint32_t max);
            bool isAutoGain();

            void enableTrigger(bool value);
            bool isTrigger();

            void setTriggerDelay(unsigned short value);
            unsigned short getTriggerDelay();

            void enableTriggerDelay(bool value);
            bool isTriggerDelay();

	void setFramerate(unsigned short value);

            void enableMirror(bool value);
            bool isMirror();

            struct lut_info_t
            {
                uint32_t lut_count;
                uint32_t max_size;
            };

            lut_info_t getLUTInfo();

            void enableLUT(bool value);
            bool isLUT();

            std::vector<uint8_t> getLUT();
            void setLUT(std::vector<uint8_t> &lut);

            uint32_t getTestImage();
            void enableTestImage(bool enable, uint32_t number);

            uint32_t getFrameCount();
            void resetFrameCount();

            /**
             * Triggers one or more bus resets and reboots the FPGA
             */
            void softReset();

            /**
             * Initialise the camera using the previsously specified video mode
             * and other settings.
             */
            void initInternal() throw(CameraException);

            /**
             * Enables or disables HDR video mode
             * @param enable Is set to true,this enables HDR processing, disables it otherwise
             */

            void startCaptureInternal() throw(CameraException);
            void stopCaptureInternal() throw(CameraException);

            bool getFrameInternal(Frame &frame);

	void DummyTestMethod();

        protected:
            /**
             * Hide default constructor
             */
            Marlin() {}

            void marlinInitInternal(uint32_t index);

            inline void setFeatureMode(dc1394feature_t feature, dc1394feature_mode_t mode)
            {
                if (!this->dc_camera) return;

                dc1394error_t err;

                err = dc1394_feature_set_mode(this->dc_camera, feature, mode);

                DC1394_ERR_THROW(err, "unable to modify feature auto state");
            }

            inline dc1394feature_mode_t getFeatureMode(dc1394feature_t feature)
            {
                if (!this->dc_camera) return DC1394_FEATURE_MODE_MANUAL;

                dc1394feature_mode_t mode;
                dc1394error_t err;

                err = dc1394_feature_get_mode(this->dc_camera, feature, &mode);

                DC1394_ERR_THROW(err, "unable to query feature auto state");

                return mode;
            }

            inline void setFeatureValue(dc1394feature_t feature, unsigned long value)
            {
                if (!this->dc_camera) return;

                dc1394error_t err;

                err = dc1394_feature_set_value(this->dc_camera, feature, value);

                DC1394_ERR_THROW(err, "unable to set feature value");
            }

            template <typename T>
                inline T getFeatureValue(dc1394feature_t feature)
                {
                    if (!this->dc_camera) return static_cast<T>(0);

                    unsigned int value;
                    dc1394error_t err;

                    err = dc1394_feature_get_value(this->dc_camera, feature, &value);

                    DC1394_ERR_THROW(err, "unable to query feature value");

                    return static_cast<T>(value);
                }

            inline void enableFeature(dc1394feature_t feature, bool enabled)
            {
                if (!this->dc_camera) return;

                dc1394error_t err;

                err = dc1394_feature_set_power(this->dc_camera, feature,
                                               static_cast<dc1394switch_t>(enabled));

                DC1394_ERR_THROW(err, "unable to set power for feature");
            }

            inline bool isFeature(dc1394feature_t feature)
            {
                if (!this->dc_camera) return false;

                dc1394switch_t value;
                dc1394error_t err;

                err = dc1394_feature_get_power(this->dc_camera, feature, &value);

                DC1394_ERR_THROW(err, "unable to query power for feature");

                return static_cast<bool>(value);
            }

            uint32_t index;

            camera_roi_t roi;

            bool awb_enabled;
            bool hdr_enabled;
            unsigned int data_depth;

            dc1394camera_t      *dc_camera;
            dc1394_t            *dc_device;
            dc1394video_frame_t *dc_frame;
    };

}

#endif /* CAMERA_MARLIN_H */

