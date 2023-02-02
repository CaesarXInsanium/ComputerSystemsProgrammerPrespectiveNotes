(define (pow a b)
  (cond ((<= b 0) 1)
        ((= b 1) a)
        ((< b 0) 0)
        (else (* a (pow a (- b 1))))))

(define w 5)

(define (add x y)
  (cond
   ((>= (+ x y)(pow 2 (- w 1))) (+ x (- y (pow 2 w)))) ;; positive overflow
   ((< (+ x y) (- 0 (pow 2 (- w 1)))) (+ x (+ y (pow 2 w)))) ;; negative overflow
   (else (+ x y))))

(define (tneg x)
  (define tmin (- (pow 2 w) 1))
  (cond ((= x tmin) x)
        ((> x tmin) (- 0 x))))

(define (test x y)
  (write (add x y))
  (newline))

(define (unsigned_mul x y)
  (mod (* x y) (pow 2 w)))

(test 20 17)
(test 24 24)
(test 23 8)
(test 2 5)
