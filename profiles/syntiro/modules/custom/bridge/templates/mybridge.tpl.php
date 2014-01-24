<?php
// $Id: mybridge.tpl.php, 10/01/2012 2:33:PM Jaffar Exp $

/**
 * @file mybridge.tpl.php
 * Default theme implementation for listing assignments in Left side blocks.
 *
 * This template collects each invocation of theme_mybridge().
 *
 * Available variables:
 * - $results['assignment']: Contains Assignment contents like Assignment Title
 * - $results['heading'] : Contains Label of this block
 */
?>
<div class="sidebar-scroll-block">
  <div class="sidebar-scroll-inner">
    <div class="my-bridge-block <?php print $results['bridge_bg']; ?><?php print $results['drag_disable']; ?>" id="<?php if($results['preview_class']): print $results['preview_class']; endif; ?>">
      <div class="my-bridge-scroll">
      <?php if (isset($results['title']['mybridge'])) { ?> <h2><?php print $results['title']['mybridge']; ?></h2> <?php } ?>
        <?php if ($results['mybridge_list']) { ?>
            <?php foreach($results['mybridge_list'] as $key => $value){ ?>
            <fieldset class="collapsible collapsed <?php print $value['active_class']; ?>">
                <legend class="collapse-processed"><?php print $value['title']; ?></legend>
                <?php if (isset($value['content'])) { ?><?php print $value['content']; ?><?php } ?>
              </fieldset>
            <?php } ?>
        <?php } ?>
      </div>
    </div>
    <div class="my-playlist-block">
      <?php if (isset($results['title']['myplaylist'])) { ?> <h2><?php print $results['title']['myplaylist']; ?></h2> <?php } ?>
      <?php if ($results['mybridge_list2']['curriculum_content'] || $results['mybridge_list2']['mycurriculum'] ) { ?>
        <ul class="playlist-list">
          <li class="recently-added"><span class="cloud-icon"></span> <?php print $results['mybridge_list2']['mycurriculum']; ?> </li>
        </ul>

          <?php if (isset($results['mybridge_list2']['curriculum_content'])) { ?>
          <ul class="expand-coll-list-playlist">
          <li class="playlist-content"></li>
            <?php if (isset($results['mybridge_list2']['curriculum_content'])) { ?>
              <?php print $results['mybridge_list2']['curriculum_content']; ?>
            <?php } ?>

           </ul>
          <?php } ?>
        <?php } ?>

    </div>
    <div class="bridge-actions-block clearfix">
      <div class="bridge-actions">
        <?php print $results['mybridge_list2']['bridge_actions'];?>
      </div>
    </div>
  </div>
 <!-- actions -->
</div>
