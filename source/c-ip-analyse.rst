================================
Introduction to Image Processing
================================
:author: David Coeurjolly


Value based Approaches
======================

Principles
----------

We only focus on values of the functions `\, f:
S\subset\mathbb{Z}^n\rightarrow Q`:math: using stochastic
representation

Important object:  **histograms**

    `H: Q \rightarrow [0,1]`:math:

    `H(i) = \frac{Card \{ p\in S \,|\, f(p) =i \}}{Card S}`:math:


The image can be seen as a random variable with probability density
function `H`:math:


Exemple: `S=[0,185]\times[0,85],\, Q=[0,255]`:math:

.. list-table::

  * - .. image:: _static/images/contourS.png
       :width: 100%
       :align: center
    - .. image:: _static/images/histocontourS.png
       :width: 110%
       :align: center



Histogram based image processing
--------------------------------

Histograms sum up colorimetric information of the image without
considering spatial relationships.


* **Image description/indexing**

  * Image characterized by its histogram (ou by descriptors     consturcted from the histogram)
  * *distance between two images* == *distance between image
    histograms* == *distance between two probability distributions*

* **Structure recognition**

  * Foreground/background analysis from histogram shape analysis
  * Noise modeling

* **Histogram optimization, equalization, ...**

* Perform transformations on the histogram and propagate the changes to image values



Histogram transformations
-------------------------

Few examples:

**Translation**

* global luminosity shift
* `H'(i) = H(i+t)`:math:

**Histogram remapping**

* e.g. using linear form `\,l: [a,b]\subset[0,1] \rightarrow [0,1]`:math:
* `H'(i) = H( a + i(b-a) )`:math:

**Inversion**

* `H'(i) = H(1 - i )`:math:

...

**More generally**

   `\phi: [0,1] \rightarrow [0,1]`:math:

   `H'(i) = H(\phi(i))`:math:

Propagation to image `f'(p) = \phi(f(p))`:math:    *<demo>*

Histogram Equalization and Histogram Specifications
---------------------------------------------------

In previous examples, `\phi`:math: was prescribed. Now, we are looking
for  `\phi`:math: to map histogram  `H`:math:
(empiric or observed) to `H'`:math: (model).

**Example: Equalization**

* Goals : equalize the intensity values *dynamic* using a *spreading*
  of the histogram
* Target distribution `H'`:math: : uniform distribution
* Effect: contrast enhancing


.. list-table::


  * - .. image:: _static/images/len_dark.png
       :width: 50%
       :align: center
    - .. image:: _static/images/len_egal.png
       :width: 50%
       :align: center

  * - .. image:: _static/images/histolen_dark.png
       :width: 80%
       :align: center
    - .. image:: _static/images/histolen_egal.png
       :width: 80%
       :align: center


Equalization (bis)
------------------

**Be careful** not always a good idea

.. list-table::

  * - .. image:: _static/images/contourS-egal.png
       :width: 100%
       :align: center
    - .. image:: _static/images/histocontourS-egal.png
       :width: 110%
       :align: center

Histogram based Segmentation
----------------------------

**Image Segmentation** classify pixels into classes such that
intra-class pixels share the same *visual* properties (colorimetric
information, geometrical properties ...)

Let's go back to initial image:

.. list-table::

  * - .. image:: _static/images/contourS.*
       :width: 70%
       :align: center
    - .. image:: _static/images/histocontourS.*
       :width: 80%
       :align: center

  * - .. image:: _static/images/contourS-seuil.*
       :width: 70%
       :align: center
    - .. image:: _static/images/histo-seuil.*
       :width: 80%
       :align: center

*Histogram Thresholding*

* Naive approach to get binary segmentation (2 classes)
* We can analyze statistical properties of each class to find the
  *best* threshold (variance minimization, entropic thresholding, ...)
* Use cases are quite limited

Local Approaches
================

Principles
----------

**Take into account spatial relationships between pixel values**

*Key tool: convolution*

* Image as a  function `f:\,\mathbb{R}^2\rightarrow \mathbb{R}`:math:
* We consider the result of the convolution product of `f`:math: by  `g:\,\mathbb{R}^2\rightarrow \mathbb{R}`:math:

    .. math::
       (f * g)(x,y) = \int_{-\infty}^\infty f(x-s,y-t)g(s,t)dsdt


* or a discrete version for compact support kernel `g`:math:

    .. math::
       (f * g)(x,y) = \sum_{i=-M}^M\sum_{j=-M}^M f(x-i,y-j)g(i,j)

*Algorithmically*

* Direct discrete computation of the support is *small*
* Or by regular product on Fourier space:

    .. math::
        f * g = \mathcal{F}^{-1}( \mathcal{F}(f)\cdot\mathcal{F}(g))



Fourier Space
-------------


.. list-table::

  * - .. image:: _static/images/len_std.*
       :width: 80%
       :align: center
    - .. image:: _static/images/len_spectrum.*
       :width: 80%
       :align: center


.. math::
      \mathcal{F}(u)=\int_{-\infty}^\infty f(x)\cdot e^{-2i\pi k u}dx
      \qquad {f}(x)=\int_{-\infty}^\infty \mathcal{F}(u)\cdot e^{-2i\pi k x}du

.. math::
      {\mathcal  {F}}(k)=\sum _{{n=0}}^{{{\mathrm  {N}}-1}}f(n)\cdot e^{{-2i\pi k{\frac  {n}{{\mathrm  {N}}}}}}\qquad
      f(n)={\frac  {1}{{\mathrm  {N}}}}\sum _{{k=0}}^{{{\mathrm  {N}}-1}}{\mathcal  {F}}(k)\cdot e^{{2i\pi n{\frac  {k}{{\mathrm  {N}}}}}}

(for `0\leqslant k<{\mathrm  {N}}`:math:)


Few Fourier Space Properties
----------------------------

* *Linearity* `\quad h(x)= af(x)+bg(x) \Leftrightarrow \mathcal{H}(u)=a\mathcal{F}(u)+b\mathcal{G}(u)`:math:

* *Scaling*

  .. math::
      h(x) = f(a\cdot x) \Leftrightarrow \mathcal{H}(u)=\frac{1}{|a|}\mathcal{F}\left(\frac{u}{a}\right)


* *Transaltion*

  .. math::
      h(x) = f(x_0 + x) \Leftrightarrow \mathcal{H}(u)=e^{i2\pi x_0}
      \mathcal{F}(u)

* *Modulation* for real `u_0`:math:

  .. math::
     \mathcal{H}(u)=\mathcal{F}(u+u_0) \Leftrightarrow h(x) = e^{i2\pi xu_0}f(x)

* *Convolution* 

  .. math::
     h(x) = (f*g)(x) = \int_{-\infty}^\infty f(t)g(x-t)dx\Leftrightarrow \mathcal{H}(u)=\mathcal{F}(u)\cdot\mathcal{G}(u)


* *DCT component*

  .. math::
      \mathcal{F}(0) = \int_{-\infty}^\infty f(x)dx

(magnitude of Fourier transform leads to **translation and rotational invariant** descriptors)


Illustrations
-------------
(http://www.cs.unm.edu/~brayer/vision/fourier.html)


.. list-table::

  * - .. image:: _static/images/Fourier/cosines.*

    - .. image:: _static/images/Fourier/phase.*
     
    - .. image:: _static/images/Fourier/brks_blks.*


  * - Pure cosine signals
    - Magnitude vs. Phase
    - Real image example


      
Illustrations
-------------
(http://www.cs.unm.edu/~brayer/vision/fourier.html)

.. list-table::

  * - .. image:: _static/images/Fourier/slant.*
    - .. image:: _static/images/Fourier/window.*

  * - Continuous vs. discrete FT
    - Edge effect reduction through convolution


*Periodic structure:*

.. image:: _static/images/Fourier/slant_group.*
     :width: 20%


Illustrations
-------------
(http://www.cs.unm.edu/~brayer/vision/fourier.html)

.. list-table::

  * - .. image:: _static/images/Fourier/lowpass.*
    - .. image:: _static/images/Fourier/highpass.*

  * - Lowpass filter
    - Highpass filter


Elementary Image Filtering
--------------------------
**Be careful**
    .. math::
      \int_{-\infty}^\infty g(s,t)dsdt = 1


**Smoothing / Low-pass filters**

    .. math::
       M_{3\times 3} = \frac{1}{9} \begin{bmatrix} 1 & 1 & 1\\1 &1 & 1\\1 & 1 & 1\\ \end{bmatrix}

    .. math::
       G_{3\times 3} = \frac{1}{16} \begin{bmatrix} 1 & 2 & 1\\2 &4 & 2\\1 & 2 & 1\\ \end{bmatrix}

    .. math::
       G_{5\times 5} = \frac{1}{256} \begin{bmatrix} 1 & 4 & 6 &4 & 1\\ 4 & 16 & 24 & 16 &4\\6 & 24 & 36 & 24 & 6\\ 4 & 16 & 24 & 16 &4\\1 & 4 & 6 &4 & 1\\ \end{bmatrix}



Mask Filtering Design
---------------------

**G** : Gaussian kernel approximation function

    .. math::
       g(x,y) = \frac{1}{\sqrt{2\pi}\sigma}\exp^{-  \frac{x^2+y^2}{2\sigma} }

    .. image:: _static/images/Gaussian_2d.png
      :width: 50%


`\Rightarrow`:math: *binomial coefficients, ....*

Examples
--------

.. list-table::

  * - `M_{3\times 3}`:math:
    - .. image:: _static/images/len_std.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_moy.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_moybis.*
       :width: 100%
       :align: center
  * - `G_{3\times 3}`:math:
    - .. image:: _static/images/len_std.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_G.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_Gbis.*
       :width: 100%
       :align: center
  * - `G_{5\times 5}`:math:
    - .. image:: _static/images/len_std.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_G5.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_G5bis.*
       :width: 100%
       :align: center


Noise Models
------------

**Match between filtering and noise model**

* Either as a theoretical hypothesis on the signal
* Or from knowledge on the device or acquisition system

.. list-table::

  * - Gaussian noise
    - .. image:: _static/images/len_bruitGaussien.*
       :width: 60%
       :align: center
    - .. image:: _static/images/len_bruitGaussienG.*
       :width: 60%
       :align: center

  * - Specular noise *salt/pepper*
    - .. image:: _static/images/len_bruit.*
       :width: 60%
       :align: center
    - .. image:: _static/images/len_bruitG.*
       :width: 60%
       :align: center

  * - Contour spread
    - .. image:: _static/images/len_bruit2.*
       :width: 60%
       :align: center
    - .. image:: _static/images/len_bruit2G.*
       :width: 60%
       :align: center


High pass filter
----------------

**Complementary filters to low-pass filters**



    .. math::
       M_{3\times 3} = \frac{1}{9} \begin{bmatrix} -1 & -1 & -1\\-1 &8 & -1\\-1 & -1 & -1\\ \end{bmatrix}

    .. math::
       G_{3\times 3} = \frac{1}{16} \begin{bmatrix} -1 & -2 & -1\\-2 &12 & -2\\-1 & -2 & -1\\ \end{bmatrix}


.. list-table::

  *  - .. image:: _static/images/len_std.*
        :width: 60%
        :align: center
     - .. image:: _static/images/len_hautG.*
        :width: 60%
        :align: center

Non-linear filters
------------------

**Median filter**

* In the support, we compute the median intensity

**example**
    .. math::
        \begin{bmatrix} 12 & 13 & 24\\1 &30 & 43\\3  & 15 & 20\\ \end{bmatrix}

`\Rightarrow`:math: 15

* perfect for specular noise
* good preservation of contours

...but...

* non-linear
* non analytical model in Fourier space


*complexity for a size* `m`:math: *domain?*

Example
-------

.. list-table::

  *  - .. image:: _static/images/len_bruit.*
        :width: 90%
        :align: center
     - .. image:: _static/images/len_bruitMedian.*
        :width: 90%
        :align: center



Contour Detection and Differential Estimators
=============================================

Objectives
----------

**Context**

* *Region* : set of pixels sharing the same colorimetric information
* By analogy,  *contours* are the loci high colorimetric variations


`\Rightarrow`:math: **loci if high gradient vector norm of the function** `f(x,y)`:math:

`\Rightarrow`:math: **Zero-crossing of the Laplacian** `\Delta f`:math:
...


.. list-table::

  *  - .. image:: _static/images/objects.*
        :width: 60%
        :align: center
     - .. image:: _static/images/NaturalTexture.*
        :width: 80%
        :align: center


We will focus later to segmentation process.


Image Gradient
--------------

**Definition**

    .. math::
        \nabla f(x,y) = \left (\frac{\partial f}{\partial x}(x,y),
        \frac{\partial f}{\partial y}(x,y)\right)


**Finite difference approximation**

    .. math::
       Prewitt_x = \frac{1}{3} \begin{bmatrix} -1 & 0 & 1\\-1 &0 & 1\\-1 & 0 & 1\\ \end{bmatrix}

       Sobel_x = \frac{1}{4} \begin{bmatrix} -1 & 0 & 1\\-2 &0 & 2\\-1 & 0 & 1\\ \end{bmatrix}

       Kirsch_x = \frac{1}{15} \begin{bmatrix} -3 & -3 & 5\\-3 &0 & 5\\-3 & -3 & 5\\ \end{bmatrix}

(other masks exist along specific directions  `\theta`:math:)




Image Gradient (bis)
--------------------

**Amplitude** = gradient vector norm

    .. math::
        \|\nabla f\|_2 = \sqrt{\left(\frac{\partial f}{\partial x}\right)^2 +   \left(\frac{\partial f}{\partial y}\right)^2}

        \|\nabla f\|_1 = \left |\frac{\partial f}{\partial x}\right| +   \left |\frac{\partial f}{\partial y} \right|

        \|\nabla f\|_\infty = \max\left(\left |\frac{\partial f}{\partial x}\right|, \left |\frac{\partial f}{\partial y}\right|\right)


**Orientation**


    .. math::
       \theta = atan\left( \frac{\frac{\partial f}{\partial y}}{\frac{\partial f}{\partial x}}\right)



`\Rightarrow`:math: a  contour can be characterized has pixels with
high gradient vector norm


Example
-------

.. list-table::

  *  - .. image:: _static/images/objects.*
        :align: center
     - .. image:: _static/images/objects-prewittx.*
        :align: center
     - .. image:: _static/images/objects-prewitty.*
        :align: center

(Prewitt)

Mask Design
-----------

**Gradient of ta filterer image and Gaussian smoothing filters**

    .. math::
        \nabla (f*g) = \nabla f * g = f*\nabla g

`\Rightarrow`:math: let us consider Gaussian kernel filter `g(x,y) =
\frac{1}{\sqrt{2\pi}\sigma}\exp^{- \frac{x^2+y^2}{2\sigma} }`:math:,
we have

    .. math::
         \frac{\partial g(x,y)}{\partial x} = -\frac{x}{\sigma^2\sqrt{2\pi}\sigma}\exp^{-  \frac{x^2+y^2}{2\sigma} }

.. list-table::

  *  - .. image:: _static/images/gaussien.*
        :align: center
        :width: 100%
     - .. image:: _static/images/gaussien_x.*
        :align: center
        :width: 100%
     - .. image:: _static/images/gaussien_xx.*
        :align: center
        :width: 100%
  *  - g
     - g'
     - g''

Separable Filters
-----------------

Let `g(x,y)`:math: be a convolution filter (`\equiv`:math: Impulse
response of a filter). The filter is  *separable* if

   .. math::
     g(x,y) = g_x(x,y)g_y(x,y)

Thus:

    .. math::
        f*g = g_x * (g_y*f)

and for partial derivatives:

    .. math::
       \frac{\partial (f*g)(x,y)}{\partial x} = f(x,y)* \left( g_x(x)\frac{dg_y}{dy}(y)\right)

`\Rightarrow`:math: direct consequences when implementing filters
(only 1D convolutions)

* If `g=[1\, 1 \,1]`:math: and `d = \nabla h = [-1\, 0 \,1]`:math:
  then  `Prewitt_x = g(x).d(y)`:math:

i.e. Prewitt's filter corresponds to finite difference approximation
of the result of a constant smoothing filtering of  `f`:math:


* Gaussisan filters are separable (and isotropic)


Theoretical Design of a Contour Detector
----------------------------------------

**Canny's criteria (1983)**


* Detection: minimize false answers
* Localization: the contour must be located with high precision
  (minimize the distance to *real contour*)
* Unique answer: a single answer by contour (no *ghosts*)

*Noise model + signal model + Criteria modeling + initial conditions*
`\Rightarrow`:math: *Optimal filter as solution of a PDE*

   .. math::
     2g(x) - 2\lambda_1g'(x) + 2\lambda_2g''(x) + \lambda_3 = 0

.. list-table::

  *  - .. image:: _static/images/shencastan.*
        :align: center
        :width: 70%
     - .. image:: _static/images/deriche.*
        :align: center
        :width: 70%
  * - Shen-Castan  : `c\exp^{-\alpha|x|}`:math:
    - Deriche : `c(\alpha|x|+1)\exp^{-\alpha|x|}`:math:


**The Gaussian filter is a good approximation of such optimal filters**


Contour Extraction
------------------

**Contour extraction requires gradient vector norm (or zero-crossing laplacian) thresholding**


* Naive approach:  `(x,y)`:math: belongs to a contour iff


         `\|\nabla f(x,y)\| > \sigma`:math:

* From hysteresis : `(x,y)`:math: belongs to a contour iff

        `\|\nabla f(x,y)\| > \sigma_1`:math:

or

         `\|\nabla f(x,y)\| > \sigma_2`:math: and `\exists
         (x',y')`:math: neighbor of `\exists (x,y)`:math: such that `\|\nabla f(x',y')\| > \sigma_1`:math:


* Using gradient orientation (we follow the contour in a direction
  perpendicular to the gradient)


Mathematical Morphology
=======================

Principles
----------

[Matheron, Serra, ...]

**Idea**

* Objects defined as sets
* Elementary operators based on boolean operations (union, difference)
* Notion of structuring elements
* Study of operator properies, e.g.:

  * Idempotence `f\circ f=f`:math:
  * Non-linear
  * Not reversible

* Generalizations exist to gray-level images and to any ordered
  lattice


Operators
---------

**Translation**

    .. math::
       X_p = \{ x + p\,|\, x\in X\}

**Dilation by a structuring element B**

    .. math::
       \delta_B(X) =  X \oplus B = \bigcup_{x\in X} B_x = \bigcup_{b\in B} X_b

**Erosion by a structuring element B**

    .. math::
      \epsilon_B(X) = X \ominus B = \bigcap_{b\in B} X_{-b}

**Properties**

with `\check{B} = \{ -p \,|\, p \in B\}`:math:  and  `X^c = E \setminus X`:math:

    .. math::
      (X \oplus B)^c = X^c \ominus \check{B}

    .. math::
      (X \ominus B)^c = X^c \oplus \check{B}

Illustrations
-------------

Structuring element: Euclidean disc

.. list-table::

  *  - .. image:: _static/images/Dilation.*
        :align: center
        :width: 70%
     - .. image:: _static/images/Erosion.*
        :align: center
        :width: 70%


(blue: set `X`:math:, gray circle: structuring element and cyan: result of the operators)


More operators
--------------

**Opening B**


   .. math::
     A \circ B = (A \ominus B)\oplus B \quad (\gamma)

**Closing**

   .. math::
     A \bullet B = (A \oplus B)\ominus B \quad (\phi)

.. list-table::

  *  - .. image:: _static/images/Opening.*
        :align: center
        :width: 65%
     - .. image:: _static/images/Closing.*
        :align: center
        :width: 65%

Examples
--------

3x3 structuring element

.. list-table::

  *  - .. image:: _static/images/Illustration_morpho.*
        :align: center
        :width: 70%
     - .. image:: _static/images/Illustration_ouverture.*
        :align: center
        :width: 70%
     - .. image:: _static/images/Illustration_fermeture.*
        :align: center
        :width: 70%


Properties
----------


**Properties**

* Opening is anti-extensive: `A\circ B\subseteq A`:math:
* Closing is extensive: `A \subseteq A\bullet B`:math:
* By duality
    .. math::
      A \bullet B = (A^c \circ B^c)^c

**Useful tool for granulometric analysis**

Sequence of increasing structuring elements  `B_k= B\oplus\ldots\oplus B`:math: k times

    .. math::
      \gamma_k(X) = X \circ B_k

    .. math::
      G_k = |\gamma_k(X)|

    .. math::
      PS_k = G_k(X) - G_{k+1}(X)


`G_k`:math: is called the granulometry function of `X`:math: and `PS_k`:math: the spectrum

**Intuitive explanation**

`X`:math: is defined as the union of *grains* and `G_k`:math: is the size of the set `\gamma_k(X)`:math: defined by *grains larger than* k


Example
-------


.. list-table::

  *  - .. image:: _static/images/snapAl.*
        :align: center
        :width: 70%
     - .. image:: _static/images/snapSam.*
        :align: center
        :width: 70%
  *  - .. image:: _static/images/al-result.*
        :align: center
        :width: 70%
     - .. image:: _static/images/M2DISCO8.*
        :align: center
        :width: 70%

Example
-------

 .. image:: _static/images/distrib2.*
        :align: center
        :width: 80%


Generalizations
---------------

**Operators on gray-level images**

`F,G: E\rightarrow E`:math:

   .. math::
      (F\oplus G)(x) = \sup_{y\in E} \{ F(y) + G(x-y)\}

      (F\ominus G)(x) = \inf_{y\in E} \{ F(y) - G(x-y)\}


**Example**

* Let suppose a grayscale image and a constant structuring element (whose origin is it mid-point, so-called *flat structuring element*)

   .. math::
       B = \begin{bmatrix} 0 & 0^* & 0 \end{bmatrix}

* Then

   .. math::
       \begin{bmatrix}13 &  16 & 17\\
       15 & 10 & 13\\
       16 & 9 & 15\\
        \end{bmatrix} \oplus B = ?


Generalization (bis)
--------------------


   .. math::
       \begin{bmatrix}13 &  16 & 17\\
       15 & 10 & 13\\
       16 & 9 & 15\\
        \end{bmatrix} \oplus B =   \begin{bmatrix}16 &  17 & 17\\
       15 & 15 & 13\\
       16 & 16 & 15\\
        \end{bmatrix}


Example (input)
---------------

.. image:: _static/images/objects-deg.*
        :align: center
        :width: 50%

Example (output)
----------------

.. list-table::

  *  - .. image:: _static/images/ob-dilation.*
        :align: center
        :width: 75%
     - .. image:: _static/images/erode.*
        :align: center
        :width: 75%
  *  - .. image:: _static/images/ob-closing.*
        :align: center
        :width: 75%
     - .. image:: _static/images/ob-opening.*
        :align: center
        :width: 75%





Morphogical Gradient/Laplacian
------------------------------

**Basic "à-la" finite difference definition**

* Gradient

   .. math::
     Grad_B(X) = X\oplus B - X\ominus B

* Laplacian

   .. math::
     Lap_B(X) = X\oplus B + X\ominus B - 2Id



.. list-table::

  *  - .. image:: _static/images/gradient_m.*
        :align: center
        :width: 65%
     - .. image:: _static/images/laplacian_m.*
        :align: center
        :width: 65%





**Mathemtatical model**

 Operators acting on *complete lattices* `(L, \leq)`:math:



Good morpholigical filters
--------------------------

**Principle**

Given an specific image

* Select the best structuring element(s)
* Specify the combination of fundamental operators (e.g. series of
  opening/closing)

* `\psi`:math: *is a filter iff it is increasing and idempotent*

   .. math::
     f\leq g \Rightarrow \psi(f) \leq \psi(g)

* `\phi,\gamma,\delta,\epsilon`:math: are filters

* `\phi\gamma, \gamma\phi, \phi\gamma\phi, \gamma\phi\gamma`:math: are
  filters and

   .. math::
     \gamma\leq \gamma\phi\gamma \leq \{ \gamma\phi, \phi\gamma \} \leq
     \phi\gamma\phi \leq \phi

.. list-table::

  *  - .. image:: _static/images/m_input.*
        :align: center
        :width: 100%
     - .. image:: _static/images/m_vert.*
        :align: center
        :width: 100%
     - .. image:: _static/images/m_horiz.*
        :align: center
        :width: 100%
     - .. image:: _static/images/m_union.*
        :align: center
        :width: 100%

[Soille]

Example
-------

.. image:: _static/images/snap2.*
        :align: center
        :width: 60%
