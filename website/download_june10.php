<?php
	$g_pageTitle = "SlimDX Download Page (June 2010)";
	$g_pageName = "Download";
	
	require_once("header.php");
?>

<div id="content">
	<div class="wrapper">
		<div id="left">
			<h1>June 2010</h1>
			<div class="paragraph">
				<h2>Introduction</h2>
        <p>
          The June 2010 release of SlimDX is now out!
        </p>
				<p>
          This release focused on filling in existing APIs and adding missing functionality. In addition to
          implementing most of DirectWrite and ensuring that Direct3D 11 support was feature complete, the June 2010 release also
          refactored shared shader and effect functionality into a common D3DCompiler namespace. Several new samples were added
          to showcase advanced interop features, and a .NET 4.0 build was added, along with VS 2010 support. On top of these
          additions, the usual array of bug fixes and feature enhancements were made to continue improving the stability of the
          SlimDX library.
        </p><br />
			</div>
			
			<div class="paragraph">
				<h2>.NET 2.0 End User Runtime</h2>
				<p>
				This is the package for end users.
				It works on both 32 and 64 bit systems, for all versions of Windows supported by the .NET Framework 2.0.
				If you're just trying to run a SlimDX program that someone else gave you, this is the installer you want to download.
				Developers should point users to this link, or include it with their own installers.
				However, developers should install the SDK below, not this package.
				See the documentation for more information.
				</p><br />
				<a href="http://slimdx.googlecode.com/files/SlimDX%20Runtime%20Net20%20%28June%202010%29.msi"><img src="images/install_runtime.png" alt="Latest User Runtime" /></a>
			</div>
			
			<div class="paragraph">
				<h2>Developer SDK</h2>
				<p>
				In the past, SlimDX was split into several different pieces for the core runtime, documentation, samples, and individual binaries.
				This is no longer the case; we have decided to follow the same model as the DirectX team and produce a redistributable runtime and a Developer SDK.
				The SDK includes all of the binaries, documentation, and samples.
				It also includes all of the files necessary to build custom installation packages if desired.
				The SDK supports both 32 bit and 64 bit systems.
				</p><br />
				<a href="http://slimdx.googlecode.com/files/SlimDX%20SDK%20%28June%202010%29.exe"><img src="images/install_sdk.png" alt="Latest Developer SDK" /></a>
			</div>
			
			<div class="paragraph">
				<h2>Information For Developers</h2>
				<p>If you&#x27;re new to this whole thing, read the <a href="http://slimdx.org/latestdocs/Default.aspx?topic=Programming+Guide/Getting+Started" rel="nofollow">Getting Started</a> documentation page.
				It should help get you moving.
				Other pages of interest include:</p>
				<ul>
				<li><a href="http://slimdx.org/latestdocs/Default.aspx?topic=SlimDX+Software+Development+Kit%2fWhat%27s+Changed+in+the+June+2010+SDK" rel="nofollow">What&#x27;s Changed in the June 2010 SDK</a> -- Information on the work we did for the June 2010 SDK release.</li>
				<li><a href="http://slimdx.org/" rel="nofollow">SlimDX Main Page</a> -- Our main homepage. This page makes it fairly straightforward to get to all of the other pages related to this project.</li>
				<li><a href="http://slimdx.org/latestdocs/Default.aspx?topic=Programming+Guide%2fManaged+Message+Loop" rel="nofollow">Managed Message Loop</a> -- Describes the rationale behind the recommended message loop for SlimDX applications.</li>
				<li><a href="http://slimdx.org/latestdocs/Default.aspx?topic=Programming+Guide/Debugging+Tips" rel="nofollow">Debugging Tips</a> -- Tips on how to work on and debug applications using SlimDX. It&#x27;s a really good idea to be familiar with the contents of this page, and check on it every so often, because it is updated periodically.</li>
				</ul>
			</div>
			
			<div class="paragraph">
				<h2>Remarks</h2>
				<p>
				We have updated our documentation so that it now links to the DirectX documentation for many classes, taking you straight to the original unmanaged type that a SlimDX type represents.
				However, this linking is machine generated, and we haven't filled it in for everything yet.
				If you see something that is incorrectly linked, please report it in our <a href="http://code.google.com/p/slimdx/issues/list">issue tracker</a>.
				</p><br />
			</div>
		</div>
	
		<div id="right">
			<ul class="sidemenu">
				<li><a href="http://slimdx.org/latestdocs/Default.aspx?topic=SlimDX+Software+Development+Kit%2fWhat%27s+Changed+in+the+June+2010+SDK">Release Notes</a></li>
				<li><a href="http://slimdx.org/latestdocs/default.aspx">Documentation</a></li>
				<li><a href="license.php">Licensing Information</a></li>
				<li><a href="releases.php">Previous Releases</a></li>
				<li><a href="http://www.microsoft.com/downloads/details.aspx?displaylang=en&FamilyID=3021d52b-514e-41d3-ad02-438a3ba730ba">DirectX SDK (June 2010)</a></li>
			</ul>
		</div>
		
		<div id="clear"></div>
    </div>
</div>

<?php	
	require_once("footer.php");
?>

