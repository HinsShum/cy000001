/**
 * /config/options.h
 *
 * Copyright (C) 2017 HinsShum
 *
 * platform.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#ifdef __cpluscplus
extern "c"
{
#endif /* __cpluscplus */

#if defined PLAT_CY000001
    #include "config/CY000001/options.h"
#endif

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
#endif /* __OPTIONS_H__ */
