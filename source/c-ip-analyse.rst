================================
Introduction to Image Processing
================================
:author: David Coeurjolly


Value based Approaches
======================

Principles
----------

We only focus on values of the functions  `\, f:
S\subset\mathbb{Z}^n\rightarrow Q`:math: using stochastic representation

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

Histgrams sum up colorimetric information of the image without
considering spatial relationships.


* **Image description/indexing**

  * Image characterized by its histogram (ou by descriptors     consturcted from the histogram)
  * *distance between two images* == *distance between image
    histograms* == *distance between two probability distribution*

* **Structure recognition**

  * Foreground/background analysis from histogram shape analysis
  * Noise modeling

* **Histogram optimization, equalisaion, ...**

  * Perform transformations on the histogram and propagate the changes
    to image values



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

**Image Segmentation**  classify pixels into classes such that
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

**Prendre en compte les relations spatiales entre pixels**

*Outils de base: convolution*

* L'image est vue comme une fonciton `f:\,\mathbb{R}^2\rightarrow \mathbb{R}`:math:
* On va s'intéresser au résultat du produit de convolution par `g:\,\mathbb{R}^2\rightarrow \mathbb{R}`:math:

    .. math::
       (f * g)(x,y) = \int_{-\infty}^\infty f(x-s,y-t)g(s,t)dsdt


* ou plutôt à une variante discrète à support compacte :

    .. math::
       (f * g)(x,y) = \sum_{i=-M}^M\sum_{j=-M}^M f(x-i,y-j)g(i,j)

*Algorithmiquement*

* Calcul direct dans le spacial si le support est *réduit*
* Par transformation de Fourier:

    .. math::
        f * g = \mathcal{F}^{-1}( \mathcal{F}(f)\cdot\mathcal{F}(g))



(Transformation de Fourier)
---------------------------


.. list-table::

  * - .. image:: _static/images/len_std.*
       :width: 100%
       :align: center
    - .. image:: _static/images/len_spectrum.*
       :width: 100%
       :align: center




Filtrage d'image élémentaire
----------------------------
**Attention :**
    .. math::
      \int_{-\infty}^\infty g(s,t)dsdt = 1


**Moyenneurs / passe-bas**

    .. math::
       M_{3\times 3} = \frac{1}{9} \begin{bmatrix} 1 & 1 & 1\\1 &1 & 1\\1 & 1 & 1\\ \end{bmatrix}

    .. math::
       G_{3\times 3} = \frac{1}{16} \begin{bmatrix} 1 & 2 & 1\\2 &4 & 2\\1 & 2 & 1\\ \end{bmatrix}

    .. math::
       G_{5\times 5} = \frac{1}{256} \begin{bmatrix} 1 & 4 & 6 &4 & 1\\ 4 & 16 & 24 & 16 &4\\6 & 24 & 36 & 24 & 6\\ 4 & 16 & 24 & 16 &4\\1 & 4 & 6 &4 & 1\\ \end{bmatrix}



Synthèse de masque
------------------

**G** : approximation d'un noyau de convolution Gaussien

    .. math::
       g(x,y) = \frac{1}{\sqrt{2\pi}\sigma}\exp^{-  \frac{x^2+y^2}{2\sigma} }

    .. image:: _static/images/Gaussian_2d.png
      :width: 50%


`\Rightarrow`:math: *coefficients binomiaux, ....*

Exemples
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


Modèle de bruit
---------------

**Adéquation entre le filtre et le modèle de bruit**

* Soit par hypothèse de travail
* Soit par connaissance du capteur ou de la chaîne d'acquisition

.. list-table::

  * - Bruit Gaussien
    - .. image:: _static/images/len_bruitGaussien.*
       :width: 60%
       :align: center
    - .. image:: _static/images/len_bruitGaussienG.*
       :width: 60%
       :align: center

  * - Bruit spéculaire *poivre/sel*
    - .. image:: _static/images/len_bruit.*
       :width: 60%
       :align: center
    - .. image:: _static/images/len_bruitG.*
       :width: 60%
       :align: center

  * - Éparpillement de contours
    - .. image:: _static/images/len_bruit2.*
       :width: 60%
       :align: center
    - .. image:: _static/images/len_bruit2G.*
       :width: 60%
       :align: center


Filtres passe-haut
------------------

**Opération complémentaire à un filtrage passe-bas**  `\,M_{haut} = Id - M_{bas}`:math:



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

Filtres non-linéaires
---------------------

**Filtre médian**

* Dans le support, on calcul la valeur médiane des intensités

*exemple*
    .. math::
        \begin{bmatrix} 12 & 13 & 24\\1 &30 & 43\\3  & 15 & 20\\ \end{bmatrix}

`\Rightarrow`:math: 15

* idéal pour du bruit spéculaire
* bonne préservation des contours

mais

* non-linéaire
* effet dans le spectre de Fourier non formalisable

Exemple
-------

.. list-table::

  *  - .. image:: _static/images/len_bruit.*
        :width: 90%
        :align: center
     - .. image:: _static/images/len_bruitMedian.*
        :width: 90%
        :align: center



Détecteurs de contour et opérateurs différentiels
=================================================

Objectifs
---------

**Contexte de travail**

* *Région* : ensemble de pixels homogènes d'un point de vue colorimétrique
* Par analogie, un *contour* est le lieu de variations significatives de l'information colorimétrique


`\Rightarrow`:math: **lieu de fort gradient en norme de la fonction** `f(x,y)`:math:

`\Rightarrow`:math: **Passage par zero du laplacien** `\Delta f`:math:
...


.. list-table::

  *  - .. image:: _static/images/objects.*
        :width: 60%
        :align: center
     - .. image:: _static/images/NaturalTexture.*
        :width: 80%
        :align: center


Nous reviendrons plus tard sur le problème général de segmentation


Gradient d'une image
--------------------

**Définition**

    .. math::
        \nabla f(x,y) = \left (\frac{\partial f}{\partial x}(x,y),
        \frac{\partial f}{\partial y}(x,y)\right)


**Approximation "différence finie"**

    .. math::
       Prewitt_x = \frac{1}{3} \begin{bmatrix} -1 & 0 & 1\\-1 &0 & 1\\-1 & 0 & 1\\ \end{bmatrix}

       Sobel_x = \frac{1}{4} \begin{bmatrix} -1 & 0 & 1\\-2 &0 & 1\\-1 & 0 & 2\\ \end{bmatrix}

       Kirsch_x = \frac{1}{15} \begin{bmatrix} -3 & -3 & 5\\-3 &0 & 5\\-3 & -3 & 5\\ \end{bmatrix}

(autres masques dans selon d'autres directions `\theta`:math:)




Gradient d'une image (bis)
--------------------------

**Amplitude** = norme du gradient

    .. math::
        \|\nabla f\|_2 = \sqrt{\left(\frac{\partial f}{\partial x}\right)^2 +   \left(\frac{\partial f}{\partial y}\right)^2}

        \|\nabla f\|_1 = \left |\frac{\partial f}{\partial x}\right| +   \left |\frac{\partial f}{\partial y} \right|

        \|\nabla f\|_\infty = \max\left(\left |\frac{\partial f}{\partial x}\right|, \left |\frac{\partial f}{\partial y}\right|\right)


**Orientation**


    .. math::
       \theta = atan\left( \frac{\frac{\partial f}{\partial y}}{\frac{\partial f}{\partial x}}\right)



`\Rightarrow`:math: le contour  peut être caractérisé par le lieu de forte amplitude du gradient


Exemple
-------

.. list-table::

  *  - .. image:: _static/images/objects.*
        :align: center
     - .. image:: _static/images/objects-prewittx.*
        :align: center
     - .. image:: _static/images/objects-prewitty.*
        :align: center

(Prewitt)

Synthèse de masque
------------------

**Gradient d'une image filtrée et filtre gaussien**

    .. math::
        \nabla (f*g) = \nabla f * g = f*\nabla g

`\Rightarrow`:math: supposons un filtre gaussien  `g(x,y) = \frac{1}{\sqrt{2\pi}\sigma}\exp^{-  \frac{x^2+y^2}{2\sigma} }`:math:, nous avons explicitement

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

Filtres séparables
------------------

Soit `g(x,y)`:math: la filtre de convolution (`\equiv`:math: réponse impulsionnelle du filtre). Le filtre est *séparable* si:

   .. math::
     g(x,y) = g_x(x,y)g_y(x,y)

Ainsi :

    .. math::
        f*g = g_x * (g_y*f)

et pour les dérivées partielles :

    .. math::
       \frac{\partial (f*g)(x,y)}{\partial x} = f(x,y)* \left( g_x(x)\frac{dg_y}{dy}(y)\right)

`\Rightarrow`:math: conséquences directes lorsque l'on implémente de tels filtres (convolution 1D uniquement)

* Si `g=[1\, 1 \,1]`:math: et `d = \nabla h = [-1\, 0 \,1]`:math: alors  `Prewitt_x = g(x).d(y)`:math: (i.e. Prewitt correspond au filtre associé à l'approximation en différence finie sur le resultat de la convolution de `f`:math par un filtre constant.

* Le filtrage gaussien est séparable (et isotrope!)


Validation d'un détecteur de contour
------------------------------------

**Critères de Canny (1983)**


* Détection : minimiser les fausses réponses
* Localisation : le contour  doit être localisé avec précision (minimiser la distance avec vrai contour)
* Réponse unique : une seule réponse par contour

*modèle de signal + modélisation des critères + conditions initiales* `\Rightarrow`:math: *filtre optimal solution d'une EDP*

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


**Le filtre gaussien est une approximation d'un tel filtre optimal**


De l'amplitude au contour
-------------------------

**La localistion du contour nécessite un seuillage des l'amplitude du gradient**


* Approche naïve :  `(x,y)`:math: appartient au contour ssi


         `\|\nabla f(x,y)\| > \sigma`:math:

* Par hysteresis : `(x,y)`:math: appartient au contour ssi

        `\|\nabla f(x,y)\| > \sigma_1`:math:

ou

         `\|\nabla f(x,y)\| > \sigma_2`:math: et `\exists (x',y')`:math: voisin de `\exists (x,y)`:math: tq `\|\nabla f(x',y')\| > \sigma_1`:math:


* Orientation du gradient (suivi de contour dans la direction
  orthogonale au gradient)


Mathematical Morphology
=======================

Principles
----------

[Matheron, Serra, ...]

**Idea**

* Object defined as sets
* Elementary operators based on boolean operations (union, difference)
* Notion of structuring elements
* Study of operator properies

  * Idempotence `f\circ f=f`:math:
  * Non-linear
  * Not reversible

* Generalizations exists to gray-level images and to any ordered
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
