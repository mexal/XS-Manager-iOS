%module CommonsLib
 %{
 /* Includes the header in the wrapper code */
 #include "CommonLib.h"
 #include "Person.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "CommonLib.h"
 %include "Person.h"