/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions
* and limitations under the License.
*
*
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include <algorithm>
#include <complex>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include <CL/sycl.hpp>
#include "cblas.h"
#include "onemkl/detail/config.hpp"
#include "onemkl/onemkl.hpp"
#include "onemkl_blas_helper.hpp"
#include "reference_blas_templates.hpp"
#include "test_common.hpp"
#include "test_helper.hpp"

#include <gtest/gtest.h>

using namespace cl::sycl;
using std::vector;

extern std::vector<cl::sycl::device> devices;

namespace {

template <typename fp>
int test(const device &dev, onemkl::uplo upper_lower, int n, int k, fp alpha, fp beta, int incx,
         int incy, int lda) {
    // Catch asynchronous exceptions.
    auto exception_handler = [](exception_list exceptions) {
        for (std::exception_ptr const &e : exceptions) {
            try {
                std::rethrow_exception(e);
            }
            catch (exception const &e) {
                std::cout << "Caught asynchronous SYCL exception during SBMV:\n"
                          << e.what() << std::endl
                          << "OpenCL status: " << e.get_cl_code() << std::endl;
            }
        }
    };

    queue main_queue(dev, exception_handler);
    context cxt = main_queue.get_context();
    event done;
    std::vector<event> dependencies;

    // Prepare data.
    auto ua = usm_allocator<fp, usm::alloc::shared, 64>(cxt, dev);
    vector<fp, decltype(ua)> x(ua), y(ua), A(ua);
    rand_vector(x, n, incx);
    rand_vector(y, n, incy);
    rand_matrix(A, onemkl::transpose::nontrans, n, n, lda);

    auto y_ref = y;

    // Call Reference SBMV.
    const int n_ref = n, incx_ref = incx, incy_ref = incy, lda_ref = lda;
    const int k_ref = k;
    using fp_ref    = typename ref_type_info<fp>::type;

    ::sbmv(convert_to_cblas_uplo(upper_lower), &n_ref, &k_ref, (fp_ref *)&alpha, (fp_ref *)A.data(),
           &lda_ref, (fp_ref *)x.data(), &incx_ref, (fp_ref *)&beta, (fp_ref *)y_ref.data(),
           &incy_ref);

    // Call DPC++ SBMV.

    try {
#ifdef CALL_RT_API
        done = onemkl::blas::sbmv(main_queue, upper_lower, n, k, alpha, A.data(), lda, x.data(),
                                  incx, beta, y.data(), incy, dependencies);
        done.wait();
#else
        TEST_RUN_CT(main_queue, onemkl::blas::sbmv,
                    (main_queue, upper_lower, n, k, alpha, A.data(), lda, x.data(), incx, beta,
                     y.data(), incy, dependencies));
        main_queue.wait();
#endif
    }
    catch (exception const &e) {
        std::cout << "Caught synchronous SYCL exception during SBMV:\n"
                  << e.what() << std::endl
                  << "OpenCL status: " << e.get_cl_code() << std::endl;
    }

    catch (const onemkl::backend_unsupported_exception &e) {
        return test_skipped;
    }

    catch (const std::runtime_error &error) {
        std::cout << "Error raised during execution of SBMV:\n" << error.what() << std::endl;
    }

    // Compare the results of reference implementation and DPC++ implementation.

    bool good = check_equal_vector(y, y_ref, n, incy, n, std::cout);

    return (int)good;
}

class SbmvUsmTests : public ::testing::TestWithParam<cl::sycl::device> {};

TEST_P(SbmvUsmTests, RealSinglePrecision) {
    float alpha(2.0);
    float beta(3.0);
    EXPECT_TRUEORSKIP(test<float>(GetParam(), onemkl::uplo::lower, 30, 5, alpha, beta, 2, 3, 42));
    EXPECT_TRUEORSKIP(test<float>(GetParam(), onemkl::uplo::upper, 30, 5, alpha, beta, 2, 3, 42));
    EXPECT_TRUEORSKIP(test<float>(GetParam(), onemkl::uplo::lower, 30, 5, alpha, beta, -2, -3, 42));
    EXPECT_TRUEORSKIP(test<float>(GetParam(), onemkl::uplo::upper, 30, 5, alpha, beta, -2, -3, 42));
    EXPECT_TRUEORSKIP(test<float>(GetParam(), onemkl::uplo::lower, 30, 5, alpha, beta, 1, 1, 42));
    EXPECT_TRUEORSKIP(test<float>(GetParam(), onemkl::uplo::upper, 30, 5, alpha, beta, 1, 1, 42));
}
TEST_P(SbmvUsmTests, RealDoublePrecision) {
    double alpha(2.0);
    double beta(3.0);
    EXPECT_TRUEORSKIP(test<double>(GetParam(), onemkl::uplo::lower, 30, 5, alpha, beta, 2, 3, 42));
    EXPECT_TRUEORSKIP(test<double>(GetParam(), onemkl::uplo::upper, 30, 5, alpha, beta, 2, 3, 42));
    EXPECT_TRUEORSKIP(
        test<double>(GetParam(), onemkl::uplo::lower, 30, 5, alpha, beta, -2, -3, 42));
    EXPECT_TRUEORSKIP(
        test<double>(GetParam(), onemkl::uplo::upper, 30, 5, alpha, beta, -2, -3, 42));
    EXPECT_TRUEORSKIP(test<double>(GetParam(), onemkl::uplo::lower, 30, 5, alpha, beta, 1, 1, 42));
    EXPECT_TRUEORSKIP(test<double>(GetParam(), onemkl::uplo::upper, 30, 5, alpha, beta, 1, 1, 42));
}

INSTANTIATE_TEST_SUITE_P(SbmvUsmTestSuite, SbmvUsmTests, ::testing::ValuesIn(devices),
                         ::DeviceNamePrint());

} // anonymous namespace
