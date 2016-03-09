//----------------------------------------------------------------------------------------------------------------------
/// @brief
/// simple Perlin noise class cobbled together from Computer Graphics OpenGL by F,S Hill
/// and Texturing and Modeling Ebert et-al
/// also thanks to Ian Stephenson for help and debuging tips
/// more work needs to be done to add interpolated noise functions and improve the
/// aliasing of the textures but it is ok for basic use
//----------------------------------------------------------------------------------------------------------------------

#include <memory>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>


#ifndef NOISE_H_
#define NOISE_H_

typedef struct Point
{
  float x=0.0f;
  float y=0.0f;
  float z=0.0f;
  Point()=default;
  Point(float _x, float _y, float _z)
  {
    x=_x; y=_y; z=_z;
  }
}Point_t;


template <typename Type>
class Noise
{
    static_assert(std::is_unsigned<Type>::value,"Can Only use Unsigned types");
    static_assert(std::numeric_limits<Type>::max() <= std::numeric_limits<unsigned int>::max()
      ,"Can Only use sizes up to unsigned int!");

public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a ctor dynamically allocates two tables
  //----------------------------------------------------------------------------------------------------------------------
  Noise();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor will remove tables allocated by dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~Noise();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a noise function to return a float based on input point and scale
  /// @param [in] _scale the scale to process the noise with
  /// @param [in] _p the point to sample noise from
  /// @brief returns a noise value
  //----------------------------------------------------------------------------------------------------------------------
  float noise( float _scale,const Point &_p);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief turbulance function creates higher frequency versions of noise as harmonics
  /// @param [in] _scale the scale to process the noise with
  /// @param [in] _p the point to sample noise from
  /// @brief returns a noise value
  //----------------------------------------------------------------------------------------------------------------------
  float turbulance(float _scale, const Point &_p );
  float complex(int _steps, float _persistence, float _scale, const Point &_p );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset the noise tables will also re-set the seed so must be called after setSeed is
  /// called
  //----------------------------------------------------------------------------------------------------------------------
  void resetTables();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the seed of the random number generator
  //----------------------------------------------------------------------------------------------------------------------
  inline void setSeed(int _s){m_seed=_s; resetTables();}


private :


  // have to use heap allocation as stack will be too small so
  // can't use std::array
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief noise table used for the noise generation
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<float> m_noiseTable;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief index into the noise table
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Type>  m_index;
  // the size of the unit is 4294967296 the largest we can hold!
  unsigned long long m_size;



  //----------------------------------------------------------------------------------------------------------------------
  /// @brief random number generator seed (default to 1)
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_seed=1.0;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to generate latticeNoise (from Ian Stephenson)
  /// @param [in] _i index into table
  /// @param [in] _j index into table
  /// @param [in] _k index into table
  //----------------------------------------------------------------------------------------------------------------------
  float latticeNoise(int _i, int _j, int _k);

};

template <typename Type>
Noise<Type>::Noise()
{
  // grab the size of the data and add 1.
  m_size=static_cast<unsigned  long long>(std::numeric_limits<Type>::max());
  // allocate memory
  m_noiseTable.resize(m_size);
  m_index.resize(m_size);
  unsigned long long  i=0;
  std::generate(std::begin(m_index), std::end(m_index), [&i]{ return i++; });
  resetTables();
}

//----------------------------------------------------------------------------------------------------------------------

template <typename Type>
void Noise<Type>::resetTables()
{
  // create an instance of the Mersenne Twister random number generator
  std::mt19937 gen(m_seed);
  // and create a RandFloat function
  std::uniform_real_distribution<float> randPosFloat(0.0f, 1.0f);
  // shuffle the index table randomly
  std::shuffle(std::begin(m_index), std::end(m_index), gen);

  for(auto &t : m_noiseTable)
  {
    t=randPosFloat(gen);
  }
}
template <typename Type>

//----------------------------------------------------------------------------------------------------------------------
Noise<Type>::~Noise()
{
}


//----------------------------------------------------------------------------------------------------------------------
template <typename Type>

float Noise<Type>::latticeNoise(int _i, int _j, int _k)
{

#define PERM(x) m_index[(x)&m_size]
#define INDEX(ix,iy,iz) PERM( (ix) + PERM((iy)+PERM(iz)))
// m_noiseTable[m_index[((_i) + m_index[((_j)+m_index[(_k)&255])&255])&255]];
return m_noiseTable[INDEX(_i,_j,_k)];


}

template <typename T> T lerp(T _a, T _b, float _t)
{
  T p;
  p=_a+(_b-_a)*_t;
  return p;
}

template <typename Type>
float Noise<Type>::noise(float _scale, const Point &_p)
{

  float d[2][2][2];
  Point pp;
  pp.x=_p.x * _scale ;
  pp.y=_p.y * _scale ;
  pp.z=_p.z * _scale ;

  long ix = (long) pp.x;
  long iy = (long) pp.y;
  long iz = (long) pp.z;
  float tx,ty,tz,x0,x1,x2,x3,y0,y1;
  tx=pp.x-ix; ty=pp.y-iy; tz=pp.z-iz;


  for(int k=0; k<=1; ++k)
  {
    for(int j=0; j<=1; ++j)
    {
      for(int i=0; i<=1; ++i)
      {
        d[k][j][i]=latticeNoise(ix+i,iy+j,iz+k);
      }
    }
  }

  x0=lerp(d[0][0][0],d[0][0][1],tx);
  x1=lerp(d[0][1][0],d[0][1][1],tx);
  x2=lerp(d[1][0][0],d[1][0][1],tx);
  x3=lerp(d[1][1][0],d[1][1][1],tx);
  y0=lerp(x0,x1,ty);
  y1=lerp(x2,x3,ty);
  return lerp(y0,y1,tz);
}



//----------------------------------------------------------------------------------------------------------------------
template <typename Type>

float Noise<Type>::turbulance(float _scale, const Point &_p  )
{
  float val= (noise(_scale,_p)/2.0) +
             (noise(2.0*_scale,_p)/4.0) +
             (noise(4.0*_scale,_p)/8.0) +
             (noise(8.0*_scale,_p)/16.0);
  return val;
}

//----------------------------------------------------------------------------------------------------------------------
// values for this are based on http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
//----------------------------------------------------------------------------------------------------------------------
template <typename Type>

float Noise<Type>::complex( int _steps,float _persistence,float _scale, const Point &_p )
{
  float val=0.0;

  for(int i=1; i<=_steps; ++i)
  {
    val+=(noise(i*_scale,_p)/std::pow(_persistence,i));
  }
  return val;

}
//----------------------------------------------------------------------------------------------------------------------


#endif
