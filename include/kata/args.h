// Created by Jiaheng on 2021/4/29.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#ifndef KATA_ARGS_H
#define KATA_ARGS_H

//

#define ARG_N_1(_0,  \
                _1,  \
                _2,  \
                _3,  \
                _4,  \
                _5,  \
                _6,  \
                _7,  \
                _8,  \
                _9,  \
                _10, \
                _11, \
                _12, \
                _13, \
                _14, \
                _15, \
                N,   \
                ...) \
  N

#define ARG_N_2() 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define ARG_(...) ARG_N_1(__VA_ARGS__)

//

#define ARGS(...) ARG_(0, ##__VA_ARGS__, ARG_N_2())

#endif  // KATA_ARGS_H
