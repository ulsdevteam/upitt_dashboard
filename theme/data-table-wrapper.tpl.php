<?php
//  print '<pre>';
//  var_dump(get_defined_vars()); 
//  print '</pre>';
?>
  <div class="item-list" style="font-size:smaller">
    <ul class="links">
      <li><?php print number_format(count($rows)) . ' record' . (count($rows) == 1 ? '' : 's'); ?></li>
    <?php if ($download_csv) : ?>
      <li><?php print $download_csv; ?></li>
    <?php endif; ?>
    <?php if ($search_link) : ?>
      <li><?php print $search_link; ?></li>
    <?php endif; ?>
    </ul>
  </div>
  <div><?php echo $table;?></div>
  <div><?php echo $paging;?></div>