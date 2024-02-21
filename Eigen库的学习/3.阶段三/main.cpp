#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main()
{
	cout << "<==========================>" << endl;
    // 设定一个三维点
    Eigen::Vector3d point(1.0, 2.0, 3.0);

    // 使用Z-Y-X欧拉角定义一个旋转 (假定以度为单位，并假定欧拉角分别为绕z轴旋转的角度alpha, 绕y轴旋转的角度beta 和绕x轴旋转的角度gamma)
    double alpha = M_PI / 4; // 以弧度
    double beta = M_PI / 4;
    double gamma = M_PI / 4;

    // 创建欧拉角对应的旋转 (以alpha, beta, gamma指定旋转)
    Eigen::AngleAxisd rollAngle(gamma, Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd pitchAngle(beta, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd yawAngle(alpha, Eigen::Vector3d::UnitZ());

    // 合成一个总旋转矩阵
    Eigen::Quaterniond q = yawAngle * pitchAngle * rollAngle;//将欧拉角转换成四元数
    Eigen::Matrix3d rotationMatrix = q.matrix();//将四元数转换为旋转矩阵

    // 将旋转应用于点
    Eigen::Vector3d rotatedPoint = rotationMatrix * point;//将旋转矩阵应用在一个点上

    std::cout << "Original point: " << point.transpose() << std::endl;
    std::cout << "Rotated point:  " << rotatedPoint.transpose() << std::endl;

	cout<<"<==========================>" << endl;
	
	return 0;
}
