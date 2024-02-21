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
	cout<<"<==========================>" << endl;
	Matrix<float,4,4> matrixA;
	matrixA.setZero();
	cout << matrixA << endl;

	cout << "change matrix entries" << endl;
	matrixA(0, 0) = 2;
	matrixA(0, 1) = 3;
	matrixA(2, 1) = 4;
	cout << matrixA << endl;
	cout << endl;

	Matrix3f matrixA1;
	matrixA1.setZero();
	cout << matrixA1 << endl;
	cout << endl;

	MatrixXf matrixA2(3,2);
	matrixA2.setZero();
	cout << matrixA2 << endl;
	cout << endl;

	Matrix4f matrixD;
	matrixD << 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16;
	cout << matrixD<<endl;

	MatrixXd A1(2, 2);
	MatrixXd B1(2,2);
	A1 << 1, 2,
		3, 4;
	B1 << 3, 4, 
		5, 6;
	MatrixXd C1 = A1 + B1;
	MatrixXd D1 = A1 * B1;
	cout << endl << C1 << endl;
	cout << endl << D1 << endl;

	MatrixXd At = A1.transpose();//行与列交换
	cout << endl << A1 << endl;
	cout << endl << At << endl;

	A1.transposeInPlace();
	MatrixXd R1 = A1;
	cout << endl << A1 << endl;
	
	cout << "<==========================>" << endl;
	cout << "<=====下面是官方的例子,不太懂=====>" << endl;


	// 1. 给定欧拉角和旋转矩阵given euler angles and rotation matrix
	Eigen::Vector3d euler;
	Eigen::Matrix3d rot;
	//欧拉角 euler 分别将角度转换为弧度后，存储到一个 3D 向量中。
	euler << (-176.8486 / 180.0) * M_PI, (89.1405 / 180.0)* M_PI, (4.1774 / 180.0)* M_PI;

	{
		Eigen::AngleAxisd Y(euler(2), Eigen::Vector3d::UnitZ());//绕　Z 轴
		Eigen::AngleAxisd P(euler(1), Eigen::Vector3d::UnitY());//绕 Y 轴
		Eigen::AngleAxisd R(euler(0), Eigen::Vector3d::UnitX());//绕 X 轴
		rot = Eigen::Quaterniond(Y * P * R).toRotationMatrix();//将 Y, P, R，做一连串的乘法运算，得到矩阵并且转化为四元数，最后又转回到旋转矩阵，并被保存在变量 rot 中
	}

	// 2. 利用由给定旋转矩阵计算的欧拉角生成一个新的旋转矩阵
	Eigen::Matrix3d rot_from_euler_mine;
	Eigen::Vector3d euler_mine;
	//先通过 atan2 函数和给定旋转矩阵中的特定元素，将其计算并转化为欧拉角
	euler_mine(0) = std::atan2(rot(2, 1), rot(2, 2));
	euler_mine(1) = std::atan2(-rot(2, 0), std::sqrt(rot(2, 1) * rot(2, 1) + rot(2, 2) * rot(2, 2)));
	euler_mine(2) = std::atan2(rot(1, 0), rot(0, 0));

	//用计算出来的欧拉角产生一个新的旋转矩阵 rot_from_euler_mine
	{
		Eigen::AngleAxisd Y(euler_mine(2), Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd P(euler_mine(1), Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd R(euler_mine(0), Eigen::Vector3d::UnitX());
		rot_from_euler_mine = Eigen::Quaterniond(Y * P * R).toRotationMatrix();
	}

	// 3. 利用给定的旋转矩阵，使用eulerAngles()生成新的旋转矩阵
	Eigen::Matrix3d rot_from_euler_t;
	//代表xyz顺序，euler_t(0)放的是Z的值
	//也就是: x->2 y->1 z->0,表示欧拉角是zyx
	Eigen::Vector3d euler_t = rot.eulerAngles(2, 1, 0);


	{//不加大括号,YPR定义就重复了
		Eigen::AngleAxisd Y(euler_t(0), Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd P(euler_t(1), Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd R(euler_t(2), Eigen::Vector3d::UnitX());
		rot_from_euler_t = Eigen::Quaterniond(Y * P * R).toRotationMatrix();
	}

	std::cout << "=== 1. 给的定欧拉角 =======================================================" << std::endl;
	std::cout << euler(0) * 180.0 / M_PI << ", " << euler(1) * 180.0 / M_PI << ", " << euler(2) * 180.0 / M_PI << std::endl;
	std::cout << "=== 2.给定旋转矩阵的欧拉角 (using eulerAngles()) ==========================" << std::endl;
	std::cout << euler_t(2) * 180.0 / M_PI << ", " << euler_t(1) * 180.0 / M_PI << ", " << euler_t(0) * 180.0 / M_PI << std::endl;
	std::cout << "=== 3. 给定旋转矩阵的欧拉角 (using my calculation) ========================" << std::endl;
	std::cout << euler_mine(0) * 180.0 / M_PI << ", " << euler_mine(1) * 180.0 / M_PI << ", " << euler_mine(2) * 180.0 / M_PI << std::endl;
	std::cout << "=== 1. given rotation matrix ===============================================" << std::endl;
	std::cout << rot << std::endl;
	std::cout << "=== 2. rotation matrix from my calculation =================================" << std::endl;
	std::cout << rot_from_euler_mine << std::endl;
	std::cout << "=== 3. rotation matrix from eulerAngles() ==================================" << std::endl;
	std::cout << rot_from_euler_t << std::endl;
	std::cout << "=== !! 这应该是一个单位矩阵 ================================================" << std::endl;
	std::cout << rot.inverse() * rot_from_euler_mine << std::endl;
	std::cout << "=== !! 这应该是一个单位矩阵 too ============================================" << std::endl;
	std::cout << rot.inverse() * rot_from_euler_t << std::endl;
	std::cout << std::endl;

	cout << "<==========================>" << endl;

	//测试一下大括号的用法

	int a = 0;
	{
		int b = 1;
		int c = 2;
		a += (b + c);
	}
	cout <<"a:" << a << endl;

	{
		int b = 3;
		int c = 4;
		a += (b + c);
	}
	cout << "a:" << a << endl;
	cout << "<==========================>" << endl;


	srand(time(0)); // 设置随机数种子为当前时间
	MatrixXd m = MatrixXd::Random(3, 3);//3行3列的随机矩阵(要想真正实现随机,必须设置随机种子)
	

	cout << "细节:" << endl;
	std::cout << MatrixXd::Constant(3, 3, 1.2) << std::endl;
	std::cout << m + MatrixXd::Constant(3, 3, 1.2) << std::endl;
	std::cout << (m + MatrixXd::Constant(3, 3, 1.2)) * 50 << std::endl;


	//std::cout << "m(修改前) =" << std::endl << m << std::endl;
	m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
	std::cout << "m(修改后) =" << std::endl << m << std::endl;
	
	VectorXd v(3);//三维向量
	v << 1, 2, 3;
	std::cout << "m * v =" << std::endl << m * v << std::endl;


	cout << "test agagin" << endl;
	MatrixXd mm = MatrixXd::Constant(3, 3, 1);
	VectorXd vv(3);
	vv << 1, 2, 3;
	//正确的,3行3列式x3行1列式=3行1列式
	std::cout << "mm * vv =" << std::endl << mm * vv << std::endl;

	return 0;
}
