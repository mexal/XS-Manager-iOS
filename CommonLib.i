%module CommonsLib
 %{
 /* Includes the header in the wrapper code */
 #include "CommonLib.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "CommonLib.h"