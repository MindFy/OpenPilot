/**
 * sensorPinHole.cpp
 *
 * \date 10/03/2010
 * \author jsola@laas.fr
 *
 *  \file sensorPinHole.cpp
 *
 *  ## Add a description here ##
 *
 * \ingroup rtslam
 */

#include "rtslam/pinholeTools.hpp"
#include "rtslam/sensorPinHole.hpp"
#include "rtslam/rawImageSimu.hpp"

#include "image/Image.hpp"

namespace jafar {
	namespace rtslam {
		using namespace std;
		using namespace jafar::image;


		///////////////////////////////////////
		// Class sensor pin hole
		///////////////////////////////////////

		SensorPinHole::SensorPinHole(const robot_ptr_t & _robPtr, filtered_obj_t inFilter) :
			SensorAbstract(_robPtr, inFilter) {
			type("Pin-hole-camera");
			cout << "Created pinhole." << endl;
		}

		SensorPinHole::SensorPinHole(const simulation_t dummy, const robot_ptr_t & _robPtr) :
				SensorAbstract(ObjectAbstract::FOR_SIMULATION, _robPtr) {
			type("Pin-hole-camera");
			cout << "Created pinhole." << endl;
		}

		void SensorPinHole::set_parameters(const jblas::vec4 & k, const jblas::vec & d, const jblas::vec & c) {
			intrinsic = k;
			distortion.resize(d.size());
			distortion = d;
			correction.resize(c.size());
			correction = c;
		}

		void SensorPinHole::setup(const size_t _id, const string & _name, const vec7 & _pose, const vec7 & _std, const vec4 & _k, const vec & _d, const vec & _c){
			SensorAbstract::MapObject::ObjectAbstract::setup(_id, _name);
			pose.x(_pose);
			pose.std(_std);
			set_parameters(_k, _d, _c);
		}

		void SensorPinHole::acquireRaw(){

			Image *i;
			i =  Image::loadImage("/home/agonzale/workspace/opencv/img_pan01.jpeg",1);

			rawimagesimu_ptr_t imgRawPtr(new RawImageSimu());
			imgRawPtr->setImage(i);

			this->currentRawPtr = imgRawPtr;

		}


	}
}

