<div class="content">
<table>
  <tr>
<?php foreach ($headings as $key=>$heading) : ?>
    <th><?php print $heading; ?></th>
<?php endforeach; ?>
  </tr>
<?php if (count($rows) > 1) : ?>
  <?php foreach ($rows as $row) : ?>
  <tr>
    <?php foreach ($headings as $key=>$val) : ?>
    <td><?php print $row[$key]; ?></td>
    <?php endforeach; ?>
  </tr>
  <?php endforeach; ?>
<?php else : ?>
  <tr><td><p>No results.</p></td></tr>
<?php endif; ?>
</table>
</div>
