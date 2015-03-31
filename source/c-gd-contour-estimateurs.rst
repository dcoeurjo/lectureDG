=============================
Digital Geometry:  Estimators
=============================
:author: David Coeurjolly


Principles
==========

Introduction
------------

**Objectives**

* Define estimators to compute digital version of quantities defined in Continuous space
* Demonstrate the stability of the proposed estimators
* Prove their convergence
* Check if estimated quantities are *consistent within the digital space*: regions with positive curvature match with a digital definition of convexity

**e.g.**

* Length, surface area, ...
* Tangents / normal vectors
* Curvature, ...
* Area / Volume, geometrical moments
* ...

**Algorithmic point of view**

* Evaluate/compare estimators also in terms of complexity/efficiency


Mathematical Context
--------------------

**Multigrid analysis** Gauss digitization scheme parametrized by a grid-step

  .. math::
         Dig(\mathcal{X},h) = \left (\frac{1}{h}\cdot \mathcal{X}\right )\cap \mathbb{Z}^n


.. list-table::

  * -  .. image:: _static/images/multi-ellipse-1.*
           :width: 80%
           :align: center

    -  .. image:: _static/images/multi-ellipse-2.*
           :width: 80%
           :align: center
    -  .. image:: _static/images/multi-ellipse-4.*
           :width: 80%
           :align: center





Global Quantities
=================

Definition
----------

**Idea**

* Single scalar quantity attached to a digital object `Dig(X,h)`:math:
*  E.g.:

   * Area in 2D (resp. 3D)
   * Geometrical moments:

       .. math::
            m_{pq}(\mathcal{X}) = \int_\mathcal{X} x^py^q dx dy

**Multigrid convergence definition**

.. admonition:: Def.

     A discrete geometric estimator `\tilde{E}`:math:  of some geometric quantity `E`:math: is *multigrid convergent* for a family of shapes `\mathbb{X}`:math:    and a digitization process `Dig`:math: iff for all shape `X \in \mathbb{X}`:math:,   there exists a grid step `h_X>0`:math: such that the estimate  `\tilde{E}(Dig(X,h),h)`:math: is defined for all `0<h < h_X`:math: and
       .. math::
          | \tilde{E}(Dig(X,h),h) - E(X) | \le \tau_X(h)

     where `\tau_X : \mathbb{R}^+ \rightarrow \mathbb{R}^{+}`:math: with null limit at `0`:math:. This    function is the *speed of convergence* of the estimator.

Area/Volume
-----------

**From previous lectures...**

* If `\tilde{E}(Dig(X,h)) = h^2|Dig(X,h)|`:math:, this estimator converges for convex shapes `\mathbb{X}`:math: with speed `O(h)`:math:  [Gauss, Dirichlet]
* If `\tilde{E}(Dig(X,h)) = h^2|Dig(X,h)|`:math:, this estimator converges for `C^3`:math: convex shapes `\mathbb{X}`:math: with speed `O(h^{\frac{15}{11}+\epsilon})`:math:  [Huxley]

========================== ==== ========= =======  ======= ===
Quantity                    1    0.1      0.01     0.001   ...
========================== ==== ========= =======  ======= ===
h                           1    0.1      0.01     0.001   ...
`h^{\frac{15}{11}}`:math:   1    0.04328  0.00187  0.00008 ...
========================== ==== ========= =======  ======= ===


  .. image:: _static/images/gaussConv.*
      :width: 60%
      :align: center


Step-based Length Estimation
----------------------------

**Idea**

We specify:

* A set of elementary displacement or pattern (e.g. `\rightarrow`:math: and `\nearrow`:math:)
* A weight per displacement vector
* *Length Estimation* sum of weighed occurrences of each pattern

   .. image:: _static/images/weights.*
       :width: 100%


`\Rightarrow`:math: **statistical analysis to optimize the weights to minimize errors for random distribution of segments of length** `n`:math:


* *BLUE* (Best Linear Unbiaised Estimator): `\tilde{E}(Dig(X,h))= h( 0.948n_{\rightarrow} + 1.343n_{\nearrow})`:math:



Step-based Perimeter Estimation (bis)
-------------------------------------

**Generalizarion**

* We decompose the `\partial Dig(X,h)`:math: into pattern of length `m`:math:

   .. math::
        \partial Dig(Dig(X,h)) = w_1w_2\ldots w_n\lambda
* For each pattern `w_i`:math:, we consider a weight `p(\cdot)`:math:
* The estimator is thus
    .. math::
        \tilde{E}(Dig(X,h))= h \sum_{i=1}^n p(w_i)


**Main Result**


.. admonition:: Thm.

    `\forall\,n`:math: and `\forall \, p(\cdot)`:math: the set of slopes `\alpha`:math: such that  the estimator is convergent is countable `\Rightarrow`:math: most of the time, the estimator does not converge

[Tajine,Daurat]


*Solution*  locally adapt the parameter m  ? set m as a function of h ? (`\rightarrow DSS`:math:)

DSS Based Perimeter Estimation
------------------------------

**Basic Idea**

* Compute the decompostion of the contour `\partial Dig(X,h)`:math: into maximal DSS `\{D_i\}_N`:math: (with thus `\bigcup_N D_i = \partial Dig(X,h)`:math:)
* Estimate the length by:
     .. math::
             \tilde{E}_{DSS}(Dig(X,h))= h\cdot \sum_{i=1}^n d(first_{D_i}, first_{D_{(i+1)\, mod\, N}} )


**Main result**

.. admonition:: Thm.

    `\tilde{E}_{DSS}(Dig(X,h))`:math: is multigrid convergent for convex shapes with speed `4.5h`:math:



Experimental evaluation
-----------------------

**We need**

* A family of analytical shapes on which `E`:math: is defined
* A multigrid digitization scheme

.. list-table::

   * - .. image:: _static/images/Estim/square1.*
        :width: 100%

     - .. image:: _static/images/Estim/square01.*
        :width: 100%

     - .. image:: _static/images/Estim/triangle1.*
        :width: 100%

     - .. image:: _static/images/Estim/triangle01.*
        :width: 100%

     - .. image:: _static/images/Estim/flower1-eps-converted-to.*
        :width: 100%

     - .. image:: _static/images/Estim/flower01-eps-converted-to.*
        :width: 100%

     - .. image:: _static/images/Estim/ellipse1-eps-converted-to.*
        :width: 100%

     - .. image:: _static/images/Estim/ellipse01-eps-converted-to.*
        :width: 100%

     - .. image:: _static/images/Estim/accflower1.*
        :width: 100%

     - .. image:: _static/images/Estim/accflower01.*
        :width: 100%



.. list-table::

   * -  .. image:: _static/images/Estim/lengths-ball-R10-bis.*
           :width: 100%

     -  .. image:: _static/images/Estim/lengths-ball-R1000-timings.*
           :width: 100%


Useful tool: Maximal Segment Covering
--------------------------------------

**Principle**

* Let `S_{i,j}`:math: defines a piece of the contour from index  `i`:math: to `j`:math:
* Given a *property* `P:\{ S_{i,j}\,|\,i,j\in \partial Dig(X,h) \} \rightarrow \{0,1\}`:math: (e.g. being a DSS, a DCA,...)
* P is *incremental* if

  * `\forall i \in  \partial Dig(X,h),\, P(S_{i,i})`:math:
  * `\forall i,j \in  \partial Dig(X,h),\, P(S_{i,j})\leq P(S_{next(i),j})`:math:
  * `\forall i,j \in  \partial Dig(X,h),\, P(S_{i,j})\leq P(S_{i,prev(j)})`:math:

* `S`:math: is *maximal* if `\forall S',\, S\subset S'\, \neg P(S')`:math:


**Maximal covering =** set of all maximal segment of `\partial Dig(X,h)`:math:



**Algorithmic point of view**

* If the property is dynamic (insertion/dilation at each extremity) with `O(p)`:math: per operations `\Rightarrow\, O(p\cdot n)`:math:
* DSS is dynamic `O(1)`:math:
* DSS with thickness parameter is dynamic `O(\log n)`:math:


Illustration
------------

.. list-table::

  * -  .. image:: _static/images/Estim/flower5.*
         :width: 100%
    -  .. image:: _static/images/Estim/flower5-1.*
        :width: 100%
    -  .. image:: _static/images/Estim/flower5-2.*
         :width: 100%
    -  .. image:: _static/images/Estim/flower5-3.*
         :width: 100%

  * -  .. image:: _static/images/Estim/flower5.*
         :width: 100%
    -  .. image:: _static/images/Estim/flower5-1-zoom.*
         :width: 100%
    -  .. image:: _static/images/Estim/flower5-2-zoom.*
         :width: 100%
    -  .. image:: _static/images/Estim/flower5-3-zoom.*
         :width: 100%

  * - X
    - `Dig(X,1)`:math:
    - `Dig(X,\frac{1}{2})`:math:
    - `Dig(X,\frac{1}{4})`:math:


**Useful to**

* Define local differential estimators
* Detect local concavity/convexity

From normal vector local estimator to length/surface area estimator
-------------------------------------------------------------------

**Idea** digital version of

    .. math::
         l(\gamma) =\int_\gamma n(s)\cdot ds


Hence:

   .. math::
       \tilde{E}_{norm}(Dig(X,h)) = h\cdot \sum_{s\in \partial Dig(X,h)} \tilde{n}(s)\cdot\vec{n}_{elem}(s)


   .. image:: _static/images/Estim/snapshot.*
      :width: 40%
      :align: center


**Main result: If** `\tilde{n}`:math: **uniformly converges in** `O(h^\alpha)`:math: **,**  `\tilde{E}_{norm}(Dig(X,h))`:math: **converges in** `O(h^\alpha)`:math:

Local Quantities
================

Definition of multigrid convergence
-----------------------------------


**Multigrid convergence for local geometric quantities**

.. admonition:: Def.

    The estimator `\tilde{Q}`:math: is *multigrid-convergent* for the family  `\mathbb{X}`:math: if and only if, for any `X \in \mathbb{X}`:math:, there exists a grid step `h_X>0`:math: such that the estimate    `\tilde{Q}(Dig(X,h),y,h)`:math: is defined for all  `y \in \partial{Dig(X,h)}`:math: with `0<h < h_X`:math:, and for any `x  \in \partial{X}`:math:,

      .. math::
         \forall y \in \partial{Dig(X,h)}

    with


      .. math::
         \| y - x \|_\infty \le h, \quad \left | \tilde{Q}(Dig(X,h),y,h) - Q(X,x) \right | \le \tau_{X,x}(h),

    where `\tau_{X,x}: \mathbb{R}^{+*} \rightarrow \mathbb{R}^+`:math: has null limit at 0. This function defines the speed of convergence of `\tilde{Q}`:math:  toward `Q`:math: at point x of `\partial{X}`:math:. The convergence is *uniform* for  `X`:math: when every `\tau_{X,x}`:math: is bounded from above by a function  `\tau_X`:math: independent of `x \in \partial{X}`:math: with null limit at 0


`\Rightarrow`:math: **we need a mapping** `\partial X\rightarrow\partial Dig(X,h)`:math:

`\Rightarrow`:math: **Uniform convergence is a strong constraint**


Normal/Tangent estimation
-------------------------

**Generic fitting approach**

* Fix a neighborhood `m`:math: around a point `p\in \partial Dig(X,h)`:math:
* Fit the `2m+1`:math:  digital points `\{p_i(x_i,y_i)\}`:math:  by a function `f(x_i,\vec{\beta})`:math: with parameter vector `\vec{\beta}`:math:
* *Least-square fitting* : Minimize quadratic error:

  .. math::
       S = \sum_i^{2m+1} (y_i  - f(x_i,\vec\beta)^2

E.g., `f(x_i,\vec\beta) = \beta_0 + \beta_1 x`:math: for linear fitting.


**Example: tangent vector estimator**

* `\tilde{Q}_{tan-fitting}(Dig(X,h), p, m) = \beta_1`:math: where `\beta_1`:math: is the result of a least-square linear fitting



`\Rightarrow`:math: **No convergence results for fixed** `m`:math:

DSS based Normal vector
-----------------------


**Trivial idea** Use a  kind of symmetric maximal  DSS to estimate the tangent

  .. image:: _static/images/tangente.*
      :width: 80%
      :align: center

**Algorithmic**

* Since DSS recognition is O(1)-dynamic, all tangents can be obtained in O(n)


Maximal Segment Analysis
------------------------

**More flexible approach** Maximal segment from mxaimal covering

* Given a maximal DSS with slopde `\alpha_h\in[0,1]`:math:  containing  point `P\in\partial Dig(X,h)`:math:
* We consider a local parametrization of `\partial X = \gamma(s) = (x,f(x))`:math:
* Suppose P=(0,0), we have, `\forall x\in[0,l]`:math:

   .. math::
      \alpha_hx- 2h \leq f(x) \leq \alpha_hx + 2h\, \Leftrightarrow\, \alpha_h=\frac{f(x) \pm O(h)}{x}


  .. image:: _static/images/Estim/estimationTangente.*
      :width: 60%
      :align: center


Maximal Segment Analysis (bis)
------------------------------

**If the curve is locally linear**,  `f(l) = f'(0)l`:math:, and

   .. math::
       \alpha_h=f'(0) + \frac{O(h)}{l}

**If the curve has curvature greater than** `k_{min}>0`:math:,  Taylor decomposition gives us:

    .. math::
        \alpha_h = f'(0) + O(l) + \frac{O(h)}{l}



**Convergence Result**


.. admonition:: Prop.

    .. math::
       lim_{h\rightarrow 0} \alpha_h  = f'(0)\,\Leftrightarrow\, \Omega(h^a)\leq l \leq O(h^b)

    with `0 < b \leq a < 1`:math:

`\Rightarrow`:math: *Length of maximal DSS is crucial !*



Curvature Estimation
--------------------

**Fitting an order-2 polyonmial**

* No convergence for fixed `m`:math: value


**Chord length approach**

* Idea: estimate the curvature from digital tangent length `\tilde{k} = \frac{1}{\tilde{r}}`:math: with  `\tilde{r}  = \frac{l^2}{8h} + \frac{h}{2}`:math:
* The neighborhood is locally adapted but convergence if `l = \Theta(h^{-1/2})`:math: (see below)
* Noise sensitive

**Circumscribing circle from two half-tangent**

* Idea: locally, estimate left/right half-tangents (resp. OP and PQ) and estimate `\tilde{r}=h\left(\frac{|OP| |PQ| |QO|}{4\mathcal{A}_{OPQ}}\right)`:math:
* The neighborhood is locally adapted but convergence if `l = \Theta(h^{-1/2})`:math: (see below)
* Noise sensitive



*Nice but* `l`:math: is not in `\Theta(h^{-1/2})`:math:


Maximal Segment Again
---------------------

**We need to consider the following quantities**

* `n_e`:math: the number of edges of the convex hull of `Dig(X,h)`:math:
* `n_{MS}`:math: the number of maximal segments  in the covering of `\partial Dig(X,h)`:math:
* `l_e`:math:  length of convex hull edge `e`:math:  (`l_1`:math: metric for (1)-contours)
* `l_{MS}`:math: length of a maximal segment (`l_1`:math: metric for (1)-contours)

Then, we want to compute:

* sup of `l_{MS}`:math:
* inf of `l_{MS}`:math:
* mean `l_{MS}`:math:  value



*Everything as functions of h and considering specific shape family* `\mathbb{X}`:math:


Step 1: Digital Convex Hull
---------------------------

*Convex hull of X*  smallest convex set containing point set X. As consequence of the Def, the convex hull is polygonal convex set with vertices in X


**Main result in Lattice polytope in 2D** [Barany, Zunic, Balog, Acketa,...]

.. admonition:: Thm.

   .. math::
       c_1(X) h^{-\frac{2}{3}} \leq n_e \leq c_2(X)h^{-\frac{2}{3}}

   .. math::
       \Rightarrow n_e = \Theta\left(h^{-\frac{2}{3}}\right)



(Similar results in n-D exist)


.. list-table::

  * - .. image:: _static/images/Estim/acketa.*
           :width: 100%

    - .. image:: _static/images/Estim/exempleILP.*
           :width: 100%

    - .. image:: _static/images/Estim/exempleILPcvx.*
           :width: 100%



Step 2: Number of maximal segments
----------------------------------

**Main result** [Lachaud, de Vieilleville, Feschet]

If `\partial X`:math: is convex and  `C^3`:math:

   .. math::
        \frac{n_e}{\Theta(\log(h^{-1}))} \leq n_{MS} \leq 3 n_e


*Hence*
   .. math::
      \Theta\left (\frac{h^{-\frac{2}{3}}}{\log(h^{-1})}\right ) \leq n_{MS} \leq \Theta(h^{-\frac{2}{3}})



.. list-table::

   * - .. image:: _static/images/Estim/farey-ms-conv.*
         :width: 60%
         :align: center

     - .. image:: _static/images/Estim/square-ms-conv.*
         :width: 60%
         :align: center


   * - `n_e=16\,, n_{MS}=24`:math:


     - `n_e=24\,, n_{MS}=4`:math:


Step 3: Length of convex hull edges/MS
--------------------------------------

(Length = `l_1`:math: distance for (1)-contours)

**Results on the sum of lengths**


  .. math::
        \sum_e t_e = |\partial Dig(X,h)| = \Theta(h^{-1})


*From  [Lachaud, de Vieilleville, Feschet]*

  .. math::
        |\partial Dig(X,h)| <      \sum_e t_{MS} \leq 19|\partial Dig(X,h)|

*Hence*

  .. math::
     \sum_e t_{MS} = \Theta(h^{-1})


Summary
-------

If `\partial X`:math: is convex and  `C^3`:math:



.. list-table::
  :header-rows: 1

  * - Quantity
    - Smallest MS length
    - Average MS length
    - Largest MS length

  * - `t_{MS}`:math:
    - `\Omega(h^{-\frac{1}{3}})`:math:
    - `\Theta(h^{-\frac{1}{3}}) \leq \cdot \leq \Theta(h^{-\frac{1}{3}}log(h^{-1})`:math:
    - `O(h^{-\frac{1}{2}})`:math:

  * - `ht_{MS}`:math:
    - `\Omega(h^{\frac{2}{3}})`:math:
    -  `\Theta(h^{\frac{2}{3}}) \leq \cdot \leq \Theta(h^{\frac{2}{3}}log(h^{-1}))`:math:
    -  `O(h^{\frac{1}{2}})`:math:

(*Hints* for `\bar{t}_{MS}`:math:, the lower bound = lower bound on `\sum t_{MS}`:math: / upper bound `n_{MS}`:math:, results for smallest/largest MS require couple of more steps)


`\Rightarrow`:math: **Any slope of  MS containing P provides multigrid convergent estimation of tangent at P**



Local Differential Estimator Summary
------------------------------------

**Tangent Estimation in 2D**


  .. image:: _static/images/Estim/all-tangent.*
      :width: 80%

**Curvature Estmiation in 2D**



  .. image:: _static/images/Estim/all-curvature.*
      :width: 80%



Tangent Estimation in Dimension 3
---------------------------------

**Slice based approaches**

* Each surfel belong to two 2d-curves in planes parallel to axis grids
* Compute the tangent in the two curves
* Return cross-product `\rightarrow`:math: *normal vectors*

.. list-table::

  * - .. image:: _static/images/Estim/parc.*
         :width: 100%
         :align: center

    - .. image:: _static/images/Estim/3cercles.*
         :width: 100%
         :align: center



Tangent Estimation in Dimension 3
---------------------------------

**Convolution based approaches**

Convolution of elementary normal vectors in a given neighborhood

.. list-table::

  * - .. image:: _static/images/Estim/normale_elem.*
         :width: 60%
         :align: center

    - .. image:: _static/images/Estim/normale_papier.*
         :width: 60%
         :align: center

.. image:: _static/images/Estim/snapshot2-1024x610.*
      :width: 60%
      :align: center


`\Rightarrow`:math: still have to fix a neighborhood parameter


Tangent Estimation in Dimension 3
---------------------------------

**Digital Plane Recognition  approaches**


* Around each point, *recognize* maximal digital plane

* Kind of adaptive approach for the neighborhood parameter

**... but ...**

* Properties on maximal DPS are difficult to obtain


Curvature in dimension 3
------------------------

**Mean and Gaussian curvature**


 .. image:: _static/images/Estim/curvatures.*
     :width: 80%


* Mean curvature `H =\frac{1}{2}( k_1 + k_2)`:math:
* Gaussian curvature `K = k_1 k_2`:math:


Integral based Approaches
-------------------------

**Fitting an implicit polynomial surface** is still doable but we need information on the neighborhood


**Integral Invariant approach** neighborhood in `O(h^\frac{1}{3})`:math: seems to be required

* *Idea* compute area of the intersection between a ball `B_r(x)`:math: and `X`:math: at `x\in\partial X`:math:

   .. math::
       A_r(x) = \int_{B_r(x)} \chi(p)dp

Then, from Taylor expansion and for `r\rightarrow 0`:math:

  .. math::
       A_r(x) = \frac{\pi}{2} r^2 - \frac{\kappa(X,x)}{3}r^3 + O(r^4)
  .. math::
       V_r(x) = \frac{2\pi}{3} r^3 - \frac{\pi H(X,x)}{4}r^4 + O(r^5)

Hence,

  .. math::
     \tilde{H}_r(X,x)\stackrel{def}{=} \frac{8}{3r} - \frac{4V_r(x)}{\pi r^4}


`\tilde{H}_r(X,x)\rightarrow H(X,x)`:math: by definition when `r\rightarrow 0`:math:


Toward Digital Version of Integral Invariants
---------------------------------------------


 .. image:: _static/images/Estim/integral.*
     :width: 60%
     :align: center


* Volume by `|Dig(X\cap B_r(x),h)|`:math:  `\Rightarrow`:math: first error term induced by [Gauss,Huxley] (O(h))
* plus error term induced by the Taylor expansion
* plus error term induced by difference between `x`:math: and `\hat{x}`:math: (back-projection used here)

**Main Result**


.. admonition:: Thm.

    For a family of shape with onvex `C^3`:math:-boundary and bounded curvature, `\exists h_0 \in  \mathbb{R}^+`:math:, for any `h \le h_0`:math:, setting `r=k h^{\frac{1}{3}}`:math:, we have

    .. math::
     \forall x \in \partial X, \forall \hat{x} \in \partial Dig(X,h),     \| \hat{x} -x\|_\infty \le h \Rightarrow
    .. math::
      |    \tilde{Q}(Dig(X,h),\hat{x}) - k(X,x) | \le K     h^{\frac{1}{3}}.


(similar bound in 3D)

What about Gaussian curvature
-----------------------------

**Idea**

* Instead of computing the volume of `B_r(x)\cap X`:math:, we compute its covariance matrix

   .. math::
        M_r(x)= \int_{B_r(x)}  pp^T\chi(p)dp - V_r(x)\mu_r(x)\mu_r^T(x)\,,

* Eigenvalues of `M_r(x)`:math: are such that:

 .. math::
     M_1 = \frac{\pi}{48}(3\kappa_1(x) + \kappa_2(x))r^6 + O(r^7)
 .. math::
     M_2 = \frac{2\pi}{15}r^5 - \frac{\pi}{48}(\kappa_1(x) + 3\kappa_2(x))r^6 + O(r^7)
 .. math::
     M_3 = \frac{19\pi}{480}r^5 - \frac{9\pi}{512}(\kappa_1(x) + \kappa_2(x))r^6 + O(r^7)


**Result**

Similar convergence results exist with speed `O(h^\frac{1}{3})`:math:

Experimental analysis confirms the `h^\frac{1}{3}`:math: neighborhood size


Illustrations
-------------

.. list-table::


  * - .. image:: _static/images/Estim/snapshot-K-zero.png
          :width: 100%
          :align: center


    - .. image:: _static/images/Estim/snapshot-mean-zero.png
          :width: 100%
          :align: center


    - .. image:: _static/images/Estim/LeopoldSurfaceMean_clean.png
          :width: 60%
          :align: center

    - .. image:: _static/images/Estim/al_curvature.*
          :width: 140%
          :align: center


.. list-table::

  * - .. image:: _static/images/Estim/directioncourbure1.*
          :width: 70%
          :align: center


    - .. image:: _static/images/Estim/directioncourbure2.*
          :width: 70%
          :align: center


Parameter-free Curvature Estimator
----------------------------------

**First, let's have a look to the theorem statement**


.. admonition:: Thm.

    For a family of shape with convex `C^3`:math:-boundary and bounded
    curvature, `\exists h_0 \in  \mathbb{R}^+`:math:, for any `h \le
    h_0`:math:, setting `r=k h^{\frac{1}{3}}`:math:, we have
    ............

To have the convergence, we need the radius to be in
`O(h^{\frac{1}{3}})`:math:

**We know that**

  .. math::
     \Theta(h^{\frac{1}{3}}) \leq h\bar{t}^2_{MS} \leq \Theta(h^{\frac{1}{3}}log^2(h^{-1}))


`\Rightarrow`:math: *Let's use (square of) average MS length to define r*




`\Rightarrow`:math: *Parameter-free convergence in*
`\Theta(h^{\frac{1}{3}}log(h^{-1}))`:math: *!*



`\Rightarrow`:math: *Automatic selection of the scale parameter*


Illustrations
-------------

.. list-table::


  *  - .. image:: _static/images/Estim/ScaleSpace_Flower_Global.png
          :width: 100%
          :align: center
  *  - .. image:: _static/images/Estim/ScaleSpace_Flower_Local.png
          :width: 100%
          :align: center

.. list-table::

  *  - .. image:: _static/images/Estim/Bunny_64_mean.png
          :width: 100%
          :align: center

     - .. image:: _static/images/Estim/Bunny_128_mean.png
          :width: 100%
          :align: center
     - .. image:: _static/images/Estim/Bunny_256_mean.png
          :width: 100%
          :align: center

     - .. image:: _static/images/Estim/Bunny_64_k1.png
          :width: 100%
          :align: center



Feature Selection
-----------------

**Idea** Use scale-space behavior of II estimators to classify surfels
into *flat,smooth,edge* regions

.. list-table::

  *  - .. image:: _static/images/Feature/Bunny_512_II_scale.png
          :width: 70%
          :align: center


     - .. image:: _static/images/Feature/Snow_I08_II_scale.png
          :width: 70%
          :align: center

  *  - .. image:: _static/images/Feature/OctaFlower_512_noise_II_scale.png
          :width: 70%
          :align: center

     - .. image:: _static/images/Feature/OctaFlower_512_II_scale.png
          :width: 70%
          :align: center


Other quantities/properties
===========================


Digital Convextiy
-----------------

**Simple definition**

`S \subset\mathbb{Z}^d`:math: is *digitally convex* iff there exists
convex shape `X\subset\mathbb{R}^d`:math: such that `S = X\cap\mathbb{Z}^d`:math:



.. list-table::


  * - .. image:: _static/images/Estim/conv1.*
          :width: 100%
          :align: center


    - .. image:: _static/images/Estim/conv2.*
          :width: 100%
          :align: center



Convexity and DSS
-----------------

Let `S\subset \mathbb{Z}^2`:math: be a (1)-curve

**Properties on convex hull**

* Each edge of `Conv(S)`:math: is a period of some DSS
* Each vertex of  `Conv(S)`:math: is a leaning point for some period of some DSS

**Main result** [Debled-Rennesson, Doerksen-Reiter]

.. admonition:: Thm.

     S is digitally convex `\Leftrightarrow`:math: slopes of maximal segment in the covering are *monotonic*



.. list-table::


  * - .. image:: _static/images/Estim/conv_maxseg1.*
          :width: 70%
          :align: center


    - .. image:: _static/images/Estim/conv_maxseg2.*
          :width: 70%
          :align: center
