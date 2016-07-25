<?php
//  print '<pre>';
//  var_dump(get_defined_vars()); 
//  print '</pre>';
?>
<div class="content">
<?php if ($download_csv) : ?>
<?php print $download_csv; ?>
<?php endif; ?>
<table>
  <tr>
<?php foreach ($headings as $key=>$heading) : ?>
    <th>
      <?php print $heading; ?>
    </th>
<?php endforeach; ?>
  </tr>
<?php if (count($rows) > 1) : ?>
  <?php foreach ($rows as $row) : ?>
  <tr>
    <?php foreach ($headings as $key=>$val) : ?>
    <td<?php print ($key == 'PID') ? ' nowrap' : ''; ?>>
      <?php 
      if (is_array($row[$key])) {
        print implode(", ", $row[$key]);
      }
      else {
        print $row[$key];
      }
      ?>
    </td>
    <?php endforeach; ?>
  </tr>
  <?php endforeach; ?>
<?php else : ?>
  <tr><td>No results.</td></tr>
<?php endif; ?>
</table>
</div>
