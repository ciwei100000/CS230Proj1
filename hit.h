#ifndef __HIT_H__
#define __HIT_H__

class Object;

// Records information about an intersection, which may be needed later for
// Boolean operations or for a subsequent call to Normal.
struct Hit
{
    // The primitive geometry whose surface was intersected.  This should
    // not point at a Union, Difference, or Intersection object.  Instead it
    // should point at the particular component.
    const Object* object;

    // Distance along the ray at which this occurred
    double t;

    // Was the ray entering or exiting the primitive geometry stored in
    // "object"?  This will tell you whether you will need to reverse the
    // normal that you compute.
    bool ray_exiting;
    
    Hit():object(0),t(0),ray_exiting(false)
    {}
    
    Hit()
    
    bool operator<(const Hit& h1) const
    {
        return (t < h1.t);   
    }
    
    bool operator<(const double t1) const
    {
        return (t < t1);
    }
};

#endif
