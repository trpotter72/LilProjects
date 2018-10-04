(defun getprimes (max)
"Gets the primes upto max"
(seive
  (loop for i from 2 upto max collect i)))

(defun seive (lst)
"Weeds out all multiples of whichever prime leads the list, returns prime lists"
(if (null lst)
  nil
  (cons (first lst) (seive (remove-if #'(lambda (arg) (eql 0 (mod arg (first lst)))) (rest lst))))))
