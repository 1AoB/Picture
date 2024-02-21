#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;


const double M_PI = 3.14159265358979323846;

int main()
{
	cout << "<==========================>" << endl;
    // 定义一个四元数，表示围绕Z轴旋转45度
    Eigen::Quaterniond quat(Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitZ()));

    // 打印四元数
    std::cout << "Quaternion =\n" << quat.coeffs() << std::endl; // 注意：Eigen的四元数系数是(x, y, z, w)

    // 定义一个三维向量
    Eigen::Vector3d vec(1.0, 0.0, 0.0);

    // 打印原始向量
    std::cout << "Original Vector = \n" << vec << std::endl;

    // 使用四元数旋转向量
    Eigen::Vector3d rotated_vec = quat * vec;

    // 打印旋转后的向量
    std::cout << "Rotated Vector =\n" << rotated_vec << std::endl;

    // 四元数的逆
    Eigen::Quaterniond quat_inverse = quat.inverse();

    // 使用四元数的逆旋转向量回到原始位置
    Eigen::Vector3d original_vec = quat_inverse * rotated_vec;

    // 打印原始向量(1.38778e-16约等于0了)
    std::cout << "Original Vector after reverse rotation =\n" << original_vec << std::endl;

	cout<<"<==========================>" << endl;
	
	return 0;
}
