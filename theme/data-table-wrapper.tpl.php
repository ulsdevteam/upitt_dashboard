<?php
//  print '<pre>';
// var_dump(get_defined_vars()); 
//  print '</pre>';
?>
  <div class="item-list" style="font-size:smaller">
    <ul class="links">
      <li><?php print number_format($num_found) . ' record' . ($num_found == 1 ? '' : 's'); ?></li>
    <?php if ($download_csv) : ?>
      <li><?php print $download_csv; ?></li>
    <?php endif; ?>
    <?php if ($view_all) : ?>
      <li><?php print $view_all; ?></li>
    <?php endif; ?>
    <?php if ($search_link) : ?>
      <li><?php print $search_link; ?></li>
    <?php endif; ?>
    </ul>
  </div>
  <div style="overflow-x:auto"><?php print $table;?></div>
