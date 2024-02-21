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
    // 设置要旋转的向量
    Eigen::Vector3d vec(1.0, 2.0, 3.0);

    // 打印旋转之前的向量
    std::cout << "rotated vector  =\n" << vec << std::endl;

    // 定义旋转角度
    double theta = M_PI / 4;  // 弧度

    // 设置旋转轴为z轴
    Eigen::Vector3d axis(0, 0, 1);

    // 通过 AngleAxis 获取对应旋转矩阵
    Eigen::Matrix3d rotation_matrix = Eigen::AngleAxisd(theta, axis).toRotationMatrix();

    // 打印旋转矩阵
    std::cout << "rotation matrix =\n" << rotation_matrix << std::endl;

    // 对向量应用旋转矩阵，获取旋转后的向量
    Eigen::Vector3d rotated_vec = rotation_matrix * vec;

    // 打印旋转之后的向量
    std::cout << "rotated vector  =\n" << rotated_vec << std::endl;

	cout<<"<==========================>" << endl;
	
	return 0;
}
