.. _onemkl_blas_gerc:

gerc
====


.. container::


   Computes a rank-1 update (conjugated) of a general complex matrix.



      ``gerc`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The ``gerc`` routines compute a scalar-vector-vector product and add the
   result to a general matrix. The operation is defined as


  


      A <- alpha*x*y :sup:`H` + A


   where:


   ``alpha`` is a scalar,


   ``A`` is an ``m``-by-``n`` matrix,


   ``x`` is a vector of length ``m``,


   ``y`` is vector of length ``n``.


gerc (Buffer Version)
---------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function:: void onemkl::blas::gerc(sycl::queue &queue, std::int64_t m, std::int64_t n, T alpha, sycl::buffer<T,1> &x, std::int64_t incx, sycl::buffer<T,1> &y, std::int64_t incy, sycl::buffer<T,1> &a, std::int64_t lda)
.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   m
      Number of rows of ``A``. Must be at least zero.


   n
      Number of columns of ``A``. Must be at least zero.


   alpha
      Scaling factor for the matrix-vector product.


   x
      Buffer holding input vector ``x``. The buffer must be of size at
      least (1 + (``m`` - 1)*abs(``incx``)). See `Matrix and Vector
      Storage <../matrix-storage.html>`__ for
      more details.


   incx
      Stride of vector ``x``.


   y
      Buffer holding input/output vector ``y``. The buffer must be of
      size at least (1 + (``n`` - 1)*abs(``incy``)). See `Matrix and
      Vector Storage <../matrix-storage.html>`__
      for more details.


   incy
      Stride of vector ``y``.


   a
      Buffer holding input matrix ``A``. Must have size at least
      ``lda``\ \*\ ``n``. See `Matrix and Vector
      Storage <../matrix-storage.html>`__ for
      more details.


   lda
      Leading dimension of matrix ``A``. Must be at least ``m``, and
      positive.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Buffer holding the updated matrix ``A``.


gerc (USM Version)
------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  sycl::event onemkl::blas::gerc(sycl::queue &queue, std::int64_t m, std::int64_t n, T alpha, const T *x, std::int64_t incx, const T *y, std::int64_t incy, T *a, std::int64_t lda, const sycl::vector_class<sycl::event> &dependencies = {})
   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         The queue where the routine should be executed.


      m
         Number of rows of ``A``. Must be at least zero.


      n
         Number of columns of ``A``. Must be at least zero.


      alpha
         Scaling factor for the matrix-vector product.


      x
         Pointer to the input vector ``x``. The array holding input
         vector ``x`` must be of size at least (1 + (``m`` -
         1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      y
         Pointer to the input/output vector ``y``. The array holding the
         input/output vector ``y`` must be of size at least (1 + (``n``
         - 1)*abs(``incy``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector ``y``.


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A``\ ust have size at least ``lda``\ \*\ ``n``. See `Matrix
         and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of matrix ``A``. Must be at least ``m``, and
         positive.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         Pointer to the updated matrix ``A``.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
