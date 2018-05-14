<code><span style="color: #000000">
<span style="color: #0000BB">&lt;?php<br /><br /></span><span style="color: #007700">include&nbsp;</span><span style="color: #DD0000">'common.php'</span><span style="color: #007700">;<br /><br />if&nbsp;(</span><span style="color: #0000BB">$_SERVER</span><span style="color: #007700">[</span><span style="color: #DD0000">'REQUEST_METHOD'</span><span style="color: #007700">]&nbsp;===&nbsp;</span><span style="color: #DD0000">'GET'</span><span style="color: #007700">)&nbsp;{<br />&nbsp;&nbsp;print&nbsp;</span><span style="color: #0000BB">highlight_string</span><span style="color: #007700">(</span><span style="color: #0000BB">file_get_contents</span><span style="color: #007700">(</span><span style="color: #DD0000">"sign.php"</span><span style="color: #007700">),&nbsp;</span><span style="color: #0000BB">TRUE</span><span style="color: #007700">);<br />&nbsp;&nbsp;exit(</span><span style="color: #0000BB">0</span><span style="color: #007700">);<br />}<br /><br /></span><span style="color: #0000BB">$keys&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #0000BB">get_keys</span><span style="color: #007700">();<br /></span><span style="color: #0000BB">$privkey&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #0000BB">$keys</span><span style="color: #007700">[</span><span style="color: #0000BB">0</span><span style="color: #007700">];<br /></span><span style="color: #0000BB">$pubkey&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #0000BB">$keys</span><span style="color: #007700">[</span><span style="color: #0000BB">1</span><span style="color: #007700">];<br /><br />if&nbsp;(</span><span style="color: #0000BB">$privkey&nbsp;</span><span style="color: #007700">===&nbsp;</span><span style="color: #0000BB">FALSE&nbsp;</span><span style="color: #007700">||&nbsp;</span><span style="color: #0000BB">$pubkey&nbsp;</span><span style="color: #007700">===&nbsp;</span><span style="color: #0000BB">FALSE</span><span style="color: #007700">)&nbsp;{<br />&nbsp;&nbsp;die(</span><span style="color: #DD0000">"Could&nbsp;not&nbsp;load&nbsp;keys.&nbsp;Contact&nbsp;admin.&lt;br/&gt;"</span><span style="color: #007700">);<br />}<br /><br /></span><span style="color: #0000BB">$file_info&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #0000BB">$_FILES</span><span style="color: #007700">[</span><span style="color: #DD0000">'userfile'</span><span style="color: #007700">];<br /></span><span style="color: #0000BB">check_uploaded_file</span><span style="color: #007700">(</span><span style="color: #0000BB">$file_info</span><span style="color: #007700">);<br /><br /></span><span style="color: #0000BB">$text&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #0000BB">pdf_to_text</span><span style="color: #007700">(</span><span style="color: #0000BB">$file_info</span><span style="color: #007700">[</span><span style="color: #DD0000">'tmp_name'</span><span style="color: #007700">]);<br />print&nbsp;</span><span style="color: #DD0000">"Extracted&nbsp;text:&nbsp;\"</span><span style="color: #0000BB">$text</span><span style="color: #DD0000">\"&lt;br/&gt;"</span><span style="color: #007700">;<br /><br /></span><span style="color: #0000BB">$execute_query&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #DD0000">"EXECUTE&nbsp;"</span><span style="color: #007700">;<br /></span><span style="color: #0000BB">$echo_query&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #DD0000">"ECHO&nbsp;"</span><span style="color: #007700">;<br />if&nbsp;(</span><span style="color: #0000BB">substr</span><span style="color: #007700">(</span><span style="color: #0000BB">$text</span><span style="color: #007700">,&nbsp;</span><span style="color: #0000BB">0</span><span style="color: #007700">,&nbsp;</span><span style="color: #0000BB">strlen</span><span style="color: #007700">(</span><span style="color: #0000BB">$execute_query</span><span style="color: #007700">))&nbsp;===&nbsp;</span><span style="color: #0000BB">$execute_query</span><span style="color: #007700">)&nbsp;{<br />&nbsp;&nbsp;print&nbsp;</span><span style="color: #DD0000">"I&nbsp;don't&nbsp;sign&nbsp;EXECUTE&nbsp;commands.&nbsp;Go&nbsp;away.&lt;br/&gt;"</span><span style="color: #007700">;<br />}&nbsp;else&nbsp;if&nbsp;(</span><span style="color: #0000BB">substr</span><span style="color: #007700">(</span><span style="color: #0000BB">$text</span><span style="color: #007700">,&nbsp;</span><span style="color: #0000BB">0</span><span style="color: #007700">,&nbsp;</span><span style="color: #0000BB">strlen</span><span style="color: #007700">(</span><span style="color: #0000BB">$echo_query</span><span style="color: #007700">))&nbsp;===&nbsp;</span><span style="color: #0000BB">$echo_query</span><span style="color: #007700">)&nbsp;{<br />&nbsp;&nbsp;print&nbsp;</span><span style="color: #DD0000">"I'm&nbsp;OK&nbsp;with&nbsp;ECHO&nbsp;commands.&nbsp;Here&nbsp;is&nbsp;the&nbsp;signature:&nbsp;&lt;br/&gt;"</span><span style="color: #007700">;<br />&nbsp;&nbsp;</span><span style="color: #0000BB">$data&nbsp;</span><span style="color: #007700">=&nbsp;</span><span style="color: #0000BB">file_get_contents</span><span style="color: #007700">(</span><span style="color: #0000BB">$file_info</span><span style="color: #007700">[</span><span style="color: #DD0000">'tmp_name'</span><span style="color: #007700">]);<br />&nbsp;&nbsp;</span><span style="color: #0000BB">openssl_sign</span><span style="color: #007700">(</span><span style="color: #0000BB">$data</span><span style="color: #007700">,&nbsp;</span><span style="color: #0000BB">$signature</span><span style="color: #007700">,&nbsp;</span><span style="color: #0000BB">$privkey</span><span style="color: #007700">);<br />&nbsp;&nbsp;print&nbsp;</span><span style="color: #0000BB">bin2hex</span><span style="color: #007700">(</span><span style="color: #0000BB">$signature</span><span style="color: #007700">);<br />}&nbsp;else&nbsp;{<br />&nbsp;&nbsp;print&nbsp;</span><span style="color: #DD0000">"I&nbsp;can't&nbsp;recognize&nbsp;the&nbsp;command&nbsp;type.&nbsp;Go&nbsp;away.&lt;br/&gt;"</span><span style="color: #007700">;<br />}<br /><br /></span><span style="color: #0000BB">?&gt;<br /></span>
</span>
</code>