
/**
 * Create the toolbox
 * @return {string} The toolbox xml string
 */
Blockly.Yadoms.CreateToolbox_ = function () {

    var catLogic = $.t("blockly.toolbox.catLogic");
    var catLoops = $.t("blockly.toolbox.catLoops");
    var catMath = $.t("blockly.toolbox.catMath");
    var catText = $.t("blockly.toolbox.catText");
    var catDates = $.t("blockly.toolbox.catDates");
    var catLists = $.t("blockly.toolbox.catLists");
    var catColour = $.t("blockly.toolbox.catColour");

    var catActions = $.t("blockly.toolbox.catActions");
    var catDevices = $.t("blockly.toolbox.catDevices");
    var catEnumerations = $.t("blockly.toolbox.catEnumerations");
    var catVariables = $.t("blockly.toolbox.catVariables");
    var catFunctions = $.t("blockly.toolbox.catFunctions");
    var catTemplate = $.t("blockly.toolbox.catTemplate");

    var toolbox = "<xml>";

    toolbox += "  <category name=\"" + catActions + "\" colour=\"20\">";
    toolbox += "    <block type=\"yadoms_wait_for_event\"></block>";

    toolbox += "    <block type=\"yadoms_notification_simple\">";

    toolbox += "        <value name=\"Value\">";
    toolbox += "           <shadow type=\"text\"></shadow>";
    toolbox += "        </value>";
	
    toolbox += "    </block>";
    toolbox += "    <block type=\"yadoms_sleep\">";
    toolbox += "        <value name=\"Time\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">10</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "    </block>";
    toolbox += "  </category>";

    toolbox += "  <category name=\"" + catDevices + "\" colour=\"20\">";
    toolbox += "    <block type=\"keyword-value-get\"></block>";
    toolbox += "    <block type=\"keyword-value-set\"></block>";
    toolbox += "  </category>";

    toolbox += "  <sep></sep>";
    

    toolbox += "  <category name=\"" + catLogic + "\" colour=\"210\">";
    toolbox += "     <block type=\"controls_if\"></block>";
    toolbox += "     <block type=\"logic_compare\"></block>";
    toolbox += "     <block type=\"logic_operation\"></block>";
    toolbox += "     <block type=\"logic_negate\"></block>";
    toolbox += "     <block type=\"logic_boolean\"></block>";
    toolbox += "     <block type=\"logic_null\"></block>";
    toolbox += "     <block type=\"logic_ternary\"></block>";
    toolbox += "  </category>";
    toolbox += "  <category name=\"" + catLoops + "\" colour=\"120\">";
    toolbox += "     <block type=\"infinite-loop\"></block>";
    toolbox += "     <block type=\"controls_whileUntil\"></block>";
    toolbox += "     <block type=\"controls_repeat_ext\">";
    toolbox += "        <value name=\"TIMES\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">10</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"controls_for\">";
    toolbox += "        <value name=\"FROM\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">1</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"TO\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">10</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"BY\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">1</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"controls_forEach\"></block>";
    toolbox += "     <block type=\"controls_flow_statements\"></block>";
    toolbox += "  </category>";
    toolbox += "  <category name=\"" + catMath + "\" colour=\"230\">";
    toolbox += "      <block type=\"math_number\" gap=\"32\"></block>";
    toolbox += "      <block type=\"math_arithmetic\">";
    toolbox += "        <value name=\"A\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">1</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"B\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">1</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_single\">";
    toolbox += "        <value name=\"NUM\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">9</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_trig\">";
    toolbox += "        <value name=\"NUM\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">45</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_constant\"></block>";
    toolbox += "      <block type=\"math_number_property\">";
    toolbox += "        <value name=\"NUMBER_TO_CHECK\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">0</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_change\">";
    toolbox += "        <value name=\"DELTA\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">1</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_round\">";
    toolbox += "        <value name=\"NUM\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">3.1</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_on_list\"></block>";
    toolbox += "      <block type=\"math_modulo\">";
    toolbox += "        <value name=\"DIVIDEND\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">64</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"DIVISOR\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">10</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_constrain\">";
    toolbox += "        <value name=\"VALUE\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">50</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"LOW\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">1</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"HIGH\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">100</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "      <block type=\"math_random_int\">";
    toolbox += "        <value name=\"FROM\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">1</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"TO\">";
    toolbox += "          <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">100</field>";
    toolbox += "          </shadow>";
    toolbox += "        </value>";
    toolbox += "      </block>";
    toolbox += "  </category>";
    toolbox += "  <category name=\"" + catText + "\" colour=\"160\">";
    toolbox += "     <block type=\"text\"></block>";
    toolbox += "     <block type=\"yadoms_log\">";
    toolbox += "         <value name=\"LogContent\">";
    toolbox += "            <shadow type=\"text\">";
    toolbox += "            </shadow>";
    toolbox += "         </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_join\"></block>";
    toolbox += "     <block type=\"text_append\">";
    toolbox += "       <value name=\"TEXT\">";
    toolbox += "         <shadow type=\"text\"></shadow>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_length\">";
    toolbox += "       <value name=\"VALUE\">";
    toolbox += "         <shadow type=\"text\">";
    toolbox += "           <field name=\"TEXT\">abc</field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_isEmpty\">";
    toolbox += "       <value name=\"VALUE\">";
    toolbox += "         <shadow type=\"text\">";
    toolbox += "           <field name=\"TEXT\"></field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_indexOf\">";
    toolbox += "       <value name=\"VALUE\">";
    toolbox += "         <block type=\"variables_get\">";
    toolbox += "           <field name=\"VAR\">text</field>";
    toolbox += "         </block>";
    toolbox += "       </value>";
    toolbox += "       <value name=\"FIND\">";
    toolbox += "         <shadow type=\"text\">";
    toolbox += "           <field name=\"TEXT\">abc</field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_charAt\">";
    toolbox += "       <value name=\"VALUE\">";
    toolbox += "         <block type=\"variables_get\">";
    toolbox += "           <field name=\"VAR\">text</field>";
    toolbox += "         </block>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_getSubstring\">";
    toolbox += "       <value name=\"STRING\">";
    toolbox += "         <block type=\"variables_get\">";
    toolbox += "           <field name=\"VAR\">text</field>";
    toolbox += "         </block>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_changeCase\">";
    toolbox += "       <value name=\"TEXT\">";
    toolbox += "         <shadow type=\"text\">";
    toolbox += "           <field name=\"TEXT\">abc</field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"text_trim\">";
    toolbox += "       <value name=\"TEXT\">";
    toolbox += "         <shadow type=\"text\">";
    toolbox += "           <field name=\"TEXT\">abc</field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "     </block>";
    toolbox += "  </category>";

    if (Blockly.Yadoms.EnumerationsHelper.allBlocks.length > 0) {
        toolbox += "  <category name=\"" + catEnumerations + "\" colour=\"20\">";
        $.each(Blockly.Yadoms.EnumerationsHelper.allBlocks, function (index, value) {
            toolbox += "     <block type=\"" + value + "\"></block>";
        });
        toolbox += "  </category>";
    }

    toolbox += "  <category name=\"" + catDates + "\" colour=\"260\">";
    toolbox += "    <block type=\"yadoms_date_datetime\">";
    toolbox += "        <value name=\"dateInput\">";
    toolbox += "           <block type=\"yadoms_date_everyDay\">";
    toolbox += "           </block>";
    toolbox += "        </value>";	
    toolbox += "        <value name=\"timeInput\">";
    toolbox += "           <block type=\"yadoms_date_time\">";
    toolbox += "              <value name=\"hourInput\">";
    toolbox += "           	     <shadow type=\"math_number\">";
    toolbox += "                    <field name=\"NUM\">12</field>";
    toolbox += "           	     </shadow>";
    toolbox += "              </value>";
    toolbox += "              <value name=\"minuteInput\">";
    toolbox += "           	     <shadow type=\"math_number\">";
    toolbox += "                    <field name=\"NUM\">00</field>";
    toolbox += "           	     </shadow>";
    toolbox += "              </value>";
    toolbox += "           </block>";
    toolbox += "        </value>";	
    toolbox += "    </block>";
    toolbox += "    <block type=\"yadoms_date_date\"></block>";
    toolbox += "    <block type=\"yadoms_date_time\">";
    toolbox += "       <value name=\"hourInput\">";
    toolbox += "         <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">12</field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "       <value name=\"minuteInput\">";
    toolbox += "         <shadow type=\"math_number\">";
    toolbox += "            <field name=\"NUM\">00</field>";
    toolbox += "         </shadow>";
    toolbox += "       </value>";
    toolbox += "    </block>";
    toolbox += "    <block type=\"yadoms_date_everyDay\"></block>";
    toolbox += "    <block type=\"yadoms_date_weekDay\"></block>";
    toolbox += "    <block type=\"yadoms_date_sunrise\"></block>";
    toolbox += "    <block type=\"yadoms_date_sunset\"></block>";
    toolbox += "    <block type=\"yadoms_date_arithmetic\"></block>";
    toolbox += "    <block type=\"yadoms_date_timespan\">";
    toolbox += "        <value name=\"hourInput\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">1</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"minuteInput\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">0</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "    </block>";
    toolbox += "    <block type=\"yadoms_date_today\"></block>";
    toolbox += "    <block type=\"yadoms_date_now\"></block>";
    toolbox += "    <block type=\"yadoms_date_extract\"></block>";
    toolbox += "  </category>";

    toolbox += "  <category name=\"" + catLists + "\" colour=\"260\">";
    toolbox += "     <block type=\"lists_create_empty\"></block>";
    toolbox += "     <block type=\"lists_create_with\"></block>";
    toolbox += "     <block type=\"lists_repeat\">";
    toolbox += "        <value name=\"NUM\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">5</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"lists_length\"></block>";
    toolbox += "     <block type=\"lists_isEmpty\"></block>";
    toolbox += "     <block type=\"lists_indexOf\">";
    toolbox += "        <value name=\"VALUE\">";
    toolbox += "           <block type=\"variables_get\">";
    toolbox += "              <field name=\"VAR\">list</field>";
    toolbox += "           </block>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"lists_getIndex\">";
    toolbox += "        <value name=\"VALUE\">";
    toolbox += "           <block type=\"variables_get\">";
    toolbox += "              <field name=\"VAR\">list</field>";
    toolbox += "           </block>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"lists_setIndex\">";
    toolbox += "        <value name=\"LIST\">";
    toolbox += "           <block type=\"variables_get\">";
    toolbox += "              <field name=\"VAR\">list</field>";
    toolbox += "           </block>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"lists_getSublist\">";
    toolbox += "        <value name=\"LIST\">";
    toolbox += "           <block type=\"variables_get\">";
    toolbox += "              <field name=\"VAR\">list</field>";
    toolbox += "           </block>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"lists_split\">";
    toolbox += "        <value name=\"DELIM\">";
    toolbox += "           <shadow type=\"text\">";
    toolbox += "              <field name=\"TEXT\">,</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "  </category>";
    toolbox += "  <category name=\"" + catColour + "\" colour=\"20\">";
    toolbox += "     <block type=\"colour_picker\"></block>";
    toolbox += "     <block type=\"colour_random\"></block>";
    toolbox += "     <block type=\"colour_rgb\">";
    toolbox += "        <value name=\"RED\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">100</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"GREEN\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">50</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"BLUE\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">0</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "     <block type=\"colour_blend\">";
    toolbox += "        <value name=\"COLOUR1\">";
    toolbox += "           <shadow type=\"colour_picker\">";
    toolbox += "              <field name=\"COLOUR\">#ff0000</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"COLOUR2\">";
    toolbox += "           <shadow type=\"colour_picker\">";
    toolbox += "              <field name=\"COLOUR\">#3333ff</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "        <value name=\"RATIO\">";
    toolbox += "           <shadow type=\"math_number\">";
    toolbox += "              <field name=\"NUM\">0.5</field>";
    toolbox += "           </shadow>";
    toolbox += "        </value>";
    toolbox += "     </block>";
    toolbox += "  </category>";

    toolbox += "  <sep></sep>";

    toolbox += "  <category name=\"" + catTemplate + "\" colour=\"0\">";
    toolbox += "    <category name=\"" + $.t("blockly.toolbox.samples.actionAfterSunset.title") + "\" colour=\"0\">";
	toolbox += '      <block type="infinite-loop" id="QgA3R8,a~o)yAe}Q*_pJ" x="87" y="38"><statement name="DO"><block type="yadoms_wait_for_event" id=":ds_^%I`sHcvckT!~O|}"><mutation storeinvariable="false"><additional0 type="yadoms_wait_for_event_mutator_datetime_become"></additional0></mutation><field name="operatorDd0">EQ</field><value name="additionalInput_part1_0"><shadow type="yadoms_date_datetime" id="I~K(HI-;yvp@WN})9|-3"></shadow><block type="yadoms_date_arithmetic" id=",(|H~LMuHnARwh^/ge2T"><field name="operator">ADD</field><value name="A"><block type="yadoms_date_sunset" id="Me%3#6y:m.1FwsAw+PEg"></block></value><value name="B"><block type="yadoms_date_timespan" id="#v)=GfQI8M}Ns;CkjE@g"><value name="hourInput"><shadow type="math_number" id="mjgbEV;|zAL7Ik]G,*H/"><field name="NUM">0</field></shadow></value><value name="minuteInput"><shadow type="math_number" id="hh,:q[%!dhSc5H},Ye/v"><field name="NUM">30</field></shadow></value></block></value></block></value><statement name="additionalInput_part2_0"><block type="yadoms_log" id="Fs77ix)wP83BVn/8jBfB"><value name="LogContent"><shadow type="text" id="Mc38`Gu*SOt;Q]%MN74K"><field name="TEXT">' + $.t("blockly.toolbox.samples.actionAfterSunset.logMessage") + '</field></shadow></value><next><block type="keyword-value-set" id="x7.{67czG=42[.nDVdWI"><mutation input_shown="true"></mutation><field name="Device">-1</field><field name="Keyword">-1</field><value name="Value"><shadow type="logic_boolean" id="@s8vp%6/SC%178=7=|#P"><field name="BOOL">TRUE</field></shadow></value><next></next></block></next></block></statement></block></statement></block>';
    toolbox += "    </category>";
	
    toolbox += "    <category name=\"" + $.t("blockly.toolbox.samples.lowBatteryLevel.title") + "\" colour=\"0\">";
	toolbox += '      <block type="infinite-loop" id="ZWS5u)%=aKN;~m1{;6vd" x="87" y="38"><statement name="DO"><block type="yadoms_wait_for_event" id="K.nzW[9U|LdT*j5(1mv0"><mutation storeinvariable="false"><additional0 type="yadoms_wait_for_event_mutator_capacity_become"></additional0></mutation><field name="capacityDd0">batteryLevel</field><field name="operatorDd0">LTE</field><value name="additionalInput_part1_0"><shadow type="math_number" id="J(H~q,;:Df,OCSn9C#u`"><field name="NUM">5</field></shadow><block type="math_number" id="]Y%fJx8ZJ#f*1^T~6wNI"><field name="NUM">5</field></block></value><statement name="additionalInput_part2_0"><block type="yadoms_log" id="nDt`OD/PkFUSU:0Cs`RV"><value name="LogContent"><shadow type="text" id=".w^=NYpnjet]R,:hojn]"><field name="TEXT">' + $.t("blockly.toolbox.samples.lowBatteryLevel.logMessage") + '</field></shadow></value></block></statement></block></statement></block> '
    toolbox += "    </category>";
	
    toolbox += "  </category>";
	
    toolbox += "  <sep></sep>";
    toolbox += "  <category name=\"" + catVariables + "\" colour=\"330\" custom=\"VARIABLE\"></category>";
    toolbox += "  <category name=\"" + catFunctions + "\" colour=\"290\" custom=\"PROCEDURE\"></category>";
    toolbox += "</xml>";
    return toolbox;
};


