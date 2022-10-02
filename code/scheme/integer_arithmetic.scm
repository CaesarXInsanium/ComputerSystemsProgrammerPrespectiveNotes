(define (pow a b)
  (cond ((<= b 0) 1)
         ((= b 1) a)
         ((< b 0) 0)
         (else (* a (pow a (- b 1))))))

(define (add x y)
  (define w 5)
  (cond
    ((>= (+ x y)(pow 2 (- w 1))) (+ x (- y (pow 2 w)))) ;; positive overflow
    ((< (+ x y) (- 0 (pow 2 (- w 1)))) (+ x (+ y (pow 2 w)))) ;; negative overflow
    (else (+ x y))))

(define (test x y)
  (write (add x y))
  (newline))

(test 20 17)
(test 24 24)
(test 23 8)
(test 2 5)
(test 12 4)
