//
//  Enums.hpp
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__


/*!
    @enum       GMContainmentType
    @group      Math
    @constant   GMContainmentTypeContains
    @constant   GMContainmentTypeDisjoint
    @constant   GMContainmentTypeIntersects
 */
enum GMContainmentType {
    GMContainmentTypeContains,
    GMContainmentTypeDisjoint,
    GMContainmentTypeIntersects,
};

/*!
    @enum       GMPlaneIntersectionType
    @group      Math
    @constant   GMPlaneIntersectionTypeFront
    @constant   GMPlaneIntersectionTypeBack
    @constant   GMPlaneIntersectionTypeIntersecting
 */
enum GMPlaneIntersectionType {
    GMPlaneIntersectionTypeFront,
    GMPlaneIntersectionTypeBack,
    GMPlaneIntersectionTypeIntersecting,
};

#endif  //#ifndef __ENUMS_HPP__

