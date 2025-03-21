/* ************************************************************************
 * Copyright 2013 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ************************************************************************/


/*
 * Declarations not supported in visual studio
 * by default
 */

#ifndef MSVC_H_
#define MSVC_H_

#ifndef EOVERFLOW
#define EOVERFLOW 1000
#endif  /* EOVERFLOW */

#if (_MSC_VER < 1900) // 1900 is msvc2015 (defining this on msvc2015 causes fatal error)
#define snprintf _snprintf
#endif

typedef long ssize_t;

#endif /* MSVS_H_ */
