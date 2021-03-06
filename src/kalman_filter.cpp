#include "kalman_filter.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

/* 
 * Please note that the Eigen library does not initialize 
 *   VectorXd or MatrixXd objects with zeros upon creation.
 */

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_ = H_in;
  R_ = R_in;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
   * TODO: predict the state
   */
  x_ = F_ * x_;
  P_ = F_ * P_ * F_.transpose() + Q_;
}

void KalmanFilter::Update(const VectorXd &meas) {
  /**
   * TODO: update the state by using Kalman Filter equations
   */
  std::cout <<"Laser update"<<std::endl;
  VectorXd z = VectorXd(2);
  z << meas[0], meas[1];
  VectorXd z_pred = H_ * x_;
  VectorXd y = z - z_pred;
  MatrixXd S = H_ * P_ * H_.transpose() + R_;
  MatrixXd K = P_ * H_.transpose() * S.inverse();

  //new estimate
  x_ = x_ + (K * y);
  long x_size = x_.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_ = (I - K * H_) * P_;
}

void KalmanFilter::UpdateEKF(const VectorXd &meas) {
  /**
   * TODO: update the state by using Extended Kalman Filter equations
   */
  std::cout <<"Radar update"<<std::endl;
  VectorXd z = VectorXd(3);
  z << meas[0], meas[1], meas[2];

  VectorXd z_pred = VectorXd(3);
  double px = x_[0];
  double py = x_[1];

  if (abs(px) < 0.0001) {
    px = 0.0001;
  }
  
  if (abs(py) < 0.0001) {
    py = 0.0001;
  }

  double vx = x_[2];
  double vy = x_[3];

  double rho = sqrt(px*px + py*py);
  double phi = atan2(py,px);
  double rho_dot = (px*vx + py*vy)/sqrt(px*px + py*py);

  z_pred << rho, phi, rho_dot;

  VectorXd y = z - z_pred;
  while (y[1] <-M_PI) { y[1] += (M_PI*2); }
  while (y[1] > M_PI) { y[1] -= (M_PI*2); }

  MatrixXd S = H_ * P_ * H_.transpose() + R_;
  MatrixXd K = P_ * H_.transpose() * S.inverse();

  //new estimate
  x_ = x_ + (K * y);
  long x_size = x_.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_ = (I - K * H_) * P_;
}
