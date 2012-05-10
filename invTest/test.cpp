#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

namespace
{
    const double Pi = 4.0 * std::atan( 1.0 );
}

double multivariatePDF( const VectorXf& obs, const VectorXf& mean, const MatrixXf& cov )
{
    Eigen::FullPivLU<MatrixXf> lu(cov);
    
    // Inverse and determinant computed together for efficiency
    // via a precursor LU decomp.
    MatrixXf covInv = lu.inverse();
    float det = lu.determinant();
    
    VectorXf diff = obs - mean;
    
    // Note that the internet reckons more numerically stable to compute
    // using cholesky decomposition
    float mdist = 0.5f * (diff.transpose() * covInv * diff)[0];
    float k = 10.0f;
    float normTerm = std::log( 1.0f / std::sqrt( std::pow( 2.0 * Pi, k ) * det ) );
    
    return normTerm - mdist;
}

int main()
{
   MatrixXf A(10, 10);

   A << 0.07896561039197658,0.009689807767750115,-0.023726423607868162,-0.050648304226115916,-0.007401018796121999,0.0022662844094768642,-0.0025247052932365842,-0.0062934937756839275,1.3057690378837455E-4,-3.951093548912259E-4,0.009689807767750115,0.0020063750144233127,-0.0015270049052670803,-0.005568712397362173,-6.841001192198033E-4,-9.554377233759025E-4,-4.0086873448635674E-4,-3.8852219167834044E-4,5.8153022661698185E-5,-2.04749410193896E-5,-0.023726423607868162,-0.0015270049052670803,0.01477180935913947,0.013551724750690977,0.004700170568791458,-0.0049092561444567615,4.544112559794103E-4,0.0034410907416615386,4.2518470667057265E-5,2.7282161867809966E-4,-0.050648304226115916,-0.005568712397362173,0.013551724750690977,0.0355307642814304,0.003354556169861396,-0.0016833686889199805,0.001765228905470581,0.003960148941090526,-9.829370421011876E-6,2.3181740470648015E-4,-0.007401018796121999,-6.841001192198033E-4,0.004700170568791458,0.003354556169861396,0.0021603738548739556,-0.0012957680715162696,-1.8657110516686107E-4,0.0010159991052583186,-6.583776641479196E-5,1.0067335395273578E-4,0.0022662844094768642,-9.554377233759025E-4,-0.0049092561444567615,-0.0016833686889199805,-0.0012957680715162696,0.0029207602088372068,1.2024009747483524E-4,-0.0011562844747389142,-7.290637853277043E-5,-1.0327376856196502E-4,-0.0025247052932365842,-4.0086873448635674E-4,4.544112559794103E-4,0.001765228905470581,-1.8657110516686107E-4,1.2024009747483524E-4,3.158810480704468E-4,1.4175058301992965E-4,3.288906676531041E-5,-4.244204539826364E-6,-0.0062934937756839275,-3.8852219167834044E-4,0.0034410907416615386,0.003960148941090526,0.0010159991052583186,-0.0011562844747389142,1.4175058301992965E-4,8.503932340330359E-4,1.1808198141250785E-5,7.620596593813107E-5,1.3057690378837455E-4,5.8153022661698185E-5,4.2518470667057265E-5,-9.829370421011876E-6,-6.583776641479196E-5,-7.290637853277043E-5,3.288906676531041E-5,1.1808198141250785E-5,9.827950083130646E-6,-3.5306700961742384E-6,-3.951093548912259E-4,-2.04749410193896E-5,2.7282161867809966E-4,2.3181740470648015E-4,1.0067335395273578E-4,-1.0327376856196502E-4,-4.244204539826364E-6,7.620596593813107E-5,-3.5306700961742384E-6,1.692623779150183E-5;

   MatrixXf acc(10, 10);
   for ( int i = 0; i < 100000; ++i )
   {
      //cout << "Here is the matrix A:\n" << A << endl;
      //cout << "The determinant of A is " << A.determinant() << endl;
      for ( int x = 0; x < 10; ++x )
      {
         for ( int y = 0; y < 10; ++y )
         {
            A(x, y) += 0.000000001;
         }
      }
      Eigen::FullPivLU<MatrixXf> lu(A);
      acc += lu.inverse();
   }
   std::cout << acc << std::endl;
}
