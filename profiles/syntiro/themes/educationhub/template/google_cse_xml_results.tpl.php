<?php
global $base_url,$user;
?>

 <div class="google-search ">
	<?php if (!$has_results): ?>
	  <div class="search-result-no-results">
	   <?php print $no_results; ?>
	  </div>
	<?php else: ?>
	 <?php if(count($results) > 0): ?>
		<div class="results">
			<?php foreach ($results as $result) { ?>
			 <div class="clearfix aff-result">
				 <div class="result-left">
					<div class="img">
					 <?php print $result['image']; ?>
					</div>
				 </div>
				 <div class="result-right">
					 <div class="result-right-inner clearfix">
						<h3><?php print $result['title']; ?></h3>
					 </div>
					 <p><?php print $result['excerpt']; ?></p>
					 <div class="external-link">
						<span class="l"><?php print l($result['url'], $result['url']); ?></span>
					 </div>
					 <div class="links">
						 <ul class="clearfix">
							<li>
							 <?php print $result['bookmark'];?>
							</li>
							<li class="affiliated-recommend">
							 <?php print $result['recommend']; ?>
							</li>
						 </ul>
						</div>
				 </div>
			 </div>
			<?php } ?>
		</div>
	 <?php endif; ?>
	 <?php if ($recommend_form): ?>
		<div class="affiliated-recommend-form">
		 <div class="art-actions-block assign-form-block" style="display: none">
			<?php print $recommend_form; ?>
		 </div>
		</div>
	 <?php endif; ?>
  <?php endif; ?>
 </div>
