.. _onemkl_blas_trsv:

trsv
====


.. container::


   Solves a system of linear equations whose coefficients are in a
   triangular matrix.



      ``trsv`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The ``trsv`` routines compute a matrix-vector product with a triangular
   band matrix. The operation is defined as



      op(A)*x = b


   where:


   op(``A``) is one of op(``A``) = ``A``, or op(``A``) =
   ``A``\ :sup:`T`, or op(``A``) = ``A``\ :sup:`H`,


   ``A`` is an ``n``-by-``n`` unit or non-unit, upper or lower
   triangular matrix,


   ``b`` and ``x`` are vectors of length ``n``.


trsv (Buffer Version)
---------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::blas::trsv(sycl::queue &queue, uplo upper_lower, transpose trans, diag unit_nonunit, std::int64_t n, std::int64_t k, sycl::buffer<T,1> &a, std::int64_t lda, sycl::buffer<T,1> &x, std::int64_t      incx)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Specifies whether ``A`` is upper or lower triangular. See :ref:`onemkl_datatypes` for more details.


   trans
      Specifies op(``A``), the transposition operation applied to ``A``. See :ref:`onemkl_datatypes` for more details.


   unit_nonunit
      Specifies whether the matrix ``A`` is unit triangular or not. See :ref:`onemkl_datatypes` for more details.


   n
      Numbers of rows and columns of ``A``. Must be at least zero.


   a
      Buffer holding input matrix ``A``. Must have size at least
      ``lda``\ \*\ ``n``. See `Matrix and Vector
      Storage <../matrix-storage.html>`__ for
      more details.


   lda
      Leading dimension of matrix ``A``. Must be at least ``n``, and
      positive.


   x
      Buffer holding the ``n``-element right-hand side vector ``b``. The
      buffer must be of size at least (1 + (``n`` - 1)*abs(``incx``)).
      See `Matrix and Vector
      Storage <../matrix-storage.html>`__ for
      more details.


   incx
      Stride of vector ``x``.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   x
      Buffer holding the solution vector ``x``.


trsv (USM Version)
------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  sycl::event onemkl::blas::trsv(sycl::queue &queue, uplo upper_lower, transpose trans, diag unit_nonunit, std::int64_t n, std::int64_t k, const T *a, std::int64_t lda, T *x, std::int64_t incx, const sycl::vector_class<sycl::event> &dependencies = {})
   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether ``A`` is upper or lower triangular. See :ref:`onemkl_datatypes` for more details.

      trans
         Specifies op(``A``), the transposition operation applied to
         ``A``. See :ref:`onemkl_datatypes` for more details.


      unit_nonunit
         Specifies whether the matrix ``A`` is unit triangular or not. See :ref:`onemkl_datatypes` for more details.


      n
         Numbers of rows and columns of ``A``. Must be at least zero.


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A`` must have size at least ``lda``\ \*\ ``n``. See `Matrix
         and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of matrix ``A``. Must be at least ``n``, and
         positive.


      x
         Pointer to the ``n``-element right-hand side vector ``b``. The
         array holding the ``n``-element right-hand side vector ``b``
         must be of size at least (1 + (``n`` - 1)*abs(``incx``)). See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      x
         Pointer to the solution vector ``x``.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
