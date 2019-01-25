//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Fulvio Piacenza: fulvio.piacenza01@universitadipavia.it
//

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

namespace NangaParbat
{
  enum E_POS_VAL_TO_INT {V_I_left = -1, V_I_inside = 0, V_I_right = +1};
  enum E_POS_INT_TO_INT {I_I_left, I_I_left_overlapping, I_I_inside, I_I_over, I_I_right_overlapping, I_I_right};

  class Interval
  {
  public:
    double min, max;
  Interval(double const& min = 0, double const& max = 0): min(min), max(max) {}

    double size()       const { return std::max(max - min, 0.); }
    bool   is_valid()   const { return max > min; }
    bool   is_unvalid() const { return !is_valid(); }
    Interval& set_unvalid()
      {
	min	= +1;
	max	= -1;
	return *this;
      }

    Interval& init_min(double const& min)
      {
	this->min = min;
	return *this;
      }
    Interval& init_max(double const& max)
      {
	this->max = max;
	return *this;
      }

    Interval& init_min_max(double const& min, double const& max)
      {
	this->min = min;
	this->max = max;
	return *this;
      }

    Interval& init(double const& a, double const& b)
      {
	if (a < b)
	  return init_min_max(a, b);
	else
	  return init_min_max(b, a);
      }

    E_POS_VAL_TO_INT position_of(double const& value) const
    {
      if (value <= min)
	return V_I_left;
      else if (max <= value)
	return V_I_right;
      else
	return V_I_inside;
    }

    bool contains(double const& value) const
    {
      return is_valid() && min < value && value < max;
    }

    bool contains_not(double const& value) const
    {
      return !contains(value);
    }

    E_POS_INT_TO_INT position_of(Interval const& I) const
    {
      /**
       * (1) : min(I) < max(I) < min(_) < max(_)
       * (2) : min(I) < min(_) < max(I) < max(_)
       * (3) : min(I) < min(_) < max(_) < max(I)
       * (4) : min(_) < min(I) < max(I) < max(_)
       * (5) : min(_) < min(I) < max(_) < max(I)
       * (6) : min(_) < max(_) < min(I) < max(I)
       */
      if (I.max < min)
	return I_I_left;// (1)
      else              // (2)-(6)
	if (I.min < min)   // (2),(3)
	  if (I.max < max)
	    return I_I_left_overlapping;// (2)
	  else
	    return I_I_over;// (3)
	else // (4)-(6)
	  if (I.min < max)// (4),(5)
	    if (I.max < max)
	      return I_I_inside;// (4)
	    else
	      return I_I_right_overlapping;// (5)
	  else
	    return I_I_right;//(6)
    }

    std::ostream& into_stream(std::ostream &os) const
      {
	return os << "[" << min << "," << max << "]";
      }
  };

  class Variable_Limit: public Interval
  {
  public:
  Variable_Limit(double const& min = 0, double const& max = 0): Interval(min, max) {}

    Variable_Limit& add_limit_min(double const& min)
      {
	this->min = std::max(min, this->min);
	return *this;
      }

    Variable_Limit& add_limit_max(double const& max)
      {
	this->max = std::min(max, this->max);
	return *this;
      }

    Variable_Limit& add_limit_min_max(double const& min, double const& max)
      {
	this->min = std::max(min, this->min);
	this->max = std::min(max, this->max);
	return *this;
      }

    Variable_Limit& add_limit(const Interval &additional_Limit)
      {
	if (is_valid() && additional_Limit.is_valid())
	  {
	    this->min = std::max(additional_Limit.min, this->min);
	    this->max = std::min(additional_Limit.max, this->max);
	  }
	else
	  set_unvalid();
	return *this;
      }

    double get_value_linear(double const& x) const
    {
      return min + x * size();
    }

    double get_value_linear_reversed(double const& x) const
    {
      return max - x * size();
    }
  };

  class Variable_Exclusion: public Interval
  {
  public:
    Variable_Exclusion& apply_to_limit(Variable_Limit &Limit)
      {
	if (is_valid() && Limit.is_valid())
	  switch (position_of(Limit))
	    {
	    case I_I_left:
	    case I_I_right:
	      set_unvalid();
	      break;
	    case (I_I_left_overlapping):
	      Limit.add_limit_max(min);
	      set_unvalid();
	      break;
	    case (I_I_inside):
	      Limit.set_unvalid();
	      set_unvalid();
	      break;
	    case (I_I_right_overlapping):
	      Limit.add_limit_min(max);
	      set_unvalid();
	      break;
	    default:
	      break;
	    }
	return *this;
      }
  };
}
