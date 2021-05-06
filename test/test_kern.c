//
// Created by germar on 08.04.21.
//

#include "../kern.c"
#include "test.h"

TEST_INIT();

static void test_trans() {
    float x[] = {0.4f, 0.8f, 0.1f, 0.66f, 0.2f};
    float y_expected[] = {0.7639f, -0.582f, 0.102f, -0.582f,
                          0.072f,  -0.582f, -0.582f};
    float y[7];
    float w[] = {
        0.3f, 0.4f,  0.199f, 0.4f,  0.2f,  //
        0.1f, -0.8f, 0.5f,   -0.2f, 0.5f,  //
        0.5f, -0.1f, -0.5f,  0.2f,  -0.5f, //
        0.1f, -0.8f, 0.5f,   -0.2f, 0.5f,  //
        0.6f, 0.3f,  1.0f,   -0.8f, 0.1f,  //
        0.1f, -0.8f, 0.5f,   -0.2f, 0.5f,  //
        0.1f, -0.8f, 0.5f,   -0.2f, 0.5f,  //
    };
    const int M = ARRAY_LENGTH(x);
    const int N = ARRAY_LENGTH(y);
    trans(1, M, N, w, x, y);
    vec_write_f32(stdout, N, y, "calculated result");
    test(vec_is_equal_f32(N, y_expected, y, 0.001) && "Calculate y = x * w");
}

static void test_train_sgd() {
    float x[] = {0.4f, 0.8f, 0.1f, 0.66f, 0.2f};
    float y[] = {0.7639f, -0.582f, 0.102f, -0.582f, 0.072f, -0.582f, -0.582f};
    float w[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //
    };

    float w_expected[] = {
        -0.30556f, -0.61112f, -0.07639f, -0.504174f, -0.15278f, //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
        -0.0408f,  -0.0816f,  -0.0102f,  -0.06732f,  -0.0204f,  //
        0.2328,    0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
        -0.0288f,  -0.0576f,  -0.0072f,  -0.04752f,  -0.0144f,  //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
    };

    const int M = ARRAY_LENGTH(x);
    const int N = ARRAY_LENGTH(y);
    train_sgd(1, M, N, x, y, 1.0, w);
    vec_write_f32(stdout, N * M, w, "calculated result");
    test(vec_is_equal_f32(N * M, w_expected, w, 0.001) &&
         "Calculate w -= N * x^T * y");
}

static void test_weight_delta() {
    float x[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.2f};
    float y[] = {0.7639f, -0.582f, 0.102f, -0.582f, 0.072f, -0.582f, -0.582f};
    float w[] = {
        -0.30556f, -0.61112f, -0.07639f, -0.504174f, -0.15278f, //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
        -0.0408f,  -0.0816f,  -0.0102f,  -0.06732f,  -0.0204f,  //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
        -0.0288f,  -0.0576f,  -0.0072f,  -0.04752f,  -0.0144f,  //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
        0.2328f,   0.4656f,   0.0582f,   0.38412f,   0.1164f,   //
    };

    float x_expected[] = {-0.781610884f, -1.563221768f, -0.195402721f,
                          -1.2896579586f, -0.390805442f};

    const int M = ARRAY_LENGTH(x);
    const int N = ARRAY_LENGTH(y);
    loss(1, M, N, w, y, x);
    vec_write_f32(stdout, M, x, "calculated result");
    test(vec_is_equal_f32(M, x_expected, x, 0.001) &&
         "Calculate dx = dy * w^T");
}

int main() {
    test_trans();
    test_train_sgd();
    test_weight_delta();
    return TEST_RESULT;
}