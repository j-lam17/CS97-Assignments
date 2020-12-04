(defun which-line ()
  "Print the current buffer line number and how many buffer lines exist."
  (interactive)
  (let ((start (point-min))
	(total (if (= (point-min) (point-max))
		   0
		   (if (= (char-before (point-max)) 10)
	       	       (count-lines (point-min) (point-max))
		       (- (count-lines (point-min) (point-max)) 1))))
	(n (line-number-at-pos)))
    (if (= start 1)
	(message "Line %d of %d" n total)
      (save-excursion
	(save-restriction
	  (widen)
	  (message "line %d (narrowed line %d)"
		   (+ n (line-number-at-pos start) -1) n))))))
