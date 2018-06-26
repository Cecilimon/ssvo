#ifndef _PREINTEGRATION_HPP_
#define _PREINTEGRATION_HPP_
#include <iostream>
#include <Eigen/Core>
#include <sophus/so3.hpp>
#include "imu_data.hpp"

namespace ssvo {

using namespace Eigen;

typedef Matrix<double, 9, 9> Matrix9d;

class Preintegration
{
public:
	Preintegration(const IMUBias &bias);

	void update(const Vector3d &measured_gyro, const Vector3d &measured_acc, const double dt);

	void correct(const IMUBias &bias);

	void reset();

	const double deltaTij() const { return delta_t_; }
	const Vector3d deltaPij() const { return delta_pos_; }
	const Vector3d deltaVij() const { return delta_vel_; }
	const Matrix3d deltaRij() const { return delta_rot_; }

	const Matrix3d jacobdRBiasGyro() const { return jacob_rot_biasgyro_; }
	const Matrix3d jacobdPBiasAcc() const { return jacob_pos_biasacc_; }
	const Matrix3d jacobdPBiasGyro() const { return jacob_pos_biasgyro_; }
	const Matrix3d jacobdVBiasAcc() const { return jacob_vel_biasacc_; }
	const Matrix3d jacobdVBiasGyro() const { return jacob_vel_biasgyro_; }

	const IMUBias getBias() const { return bias_; };
	const Matrix9d getMeasCov() const { return imu_meas_cov_; }

private:

	double delta_t_;

	//! preintegration value,  VI (33)
	Vector3d delta_pos_;
	Vector3d delta_vel_;
	Matrix3d delta_rot_;

	//! jacob for bias update, Appendix-B
	Matrix3d jacob_rot_biasgyro_;
	Matrix3d jacob_pos_biasacc_;
	Matrix3d jacob_pos_biasgyro_;
	Matrix3d jacob_vel_biasacc_;
	Matrix3d jacob_vel_biasgyro_;

	//! bias
	IMUBias bias_;

	//! covariance [dP dR dV]
	Matrix9d imu_meas_cov_;
};

std::ostream& operator<<(std::ostream& os, const Preintegration& pint);

}

#endif //_PREINTEGRATION_HPP_