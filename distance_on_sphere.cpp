#include "geometry/distance_on_sphere.hpp"

#include "base/math.hpp"

#include <algorithm>
#include <cmath>

namespace ms
{
double DistanceOnSphere(double lat1Deg, double lon1Deg, double lat2Deg, double lon2Deg)
{
  double const lat1 = base::DegToRad(lat1Deg);
  double const lat2 = base::DegToRad(lat2Deg);
  double const dlat = sin((lat2 - lat1) * 0.5);
  double const dlon = sin((base::DegToRad(lon2Deg) - base::DegToRad(lon1Deg)) * 0.5);
  double const y = dlat * dlat + dlon * dlon * cos(lat1) * cos(lat2);
  return 2.0 * atan2(sqrt(y), sqrt(std::max(0.0, 1.0 - y)));
}

double DistanceOnEarth(double lat1Deg, double lon1Deg, double lat2Deg, double lon2Deg)
{
  return kEarthRadiusMeters * DistanceOnSphere(lat1Deg, lon1Deg, lat2Deg, lon2Deg);
}

double DistanceOnEarth(LatLon const & ll1, LatLon const & ll2)
{
  return DistanceOnEarth(ll1.m_lat, ll1.m_lon, ll2.m_lat, ll2.m_lon);
}

m3::Point<double> ToVector(LatLon const & ll)
{
double lat= base::DegToRad(ll.m_lat);
double lon= base::DegToRad(ll.m_lon);
return {kEarthRadiusMeters *cos(lat)*cos(lon),
        kEarthRadiusMeters *cos(lat)*sin(lon),
        kEarthRadiusMeters *sin(lat)};
}

}  // namespace ms
