%bcond_with wayland
%bcond_with x

Name:       mmsvc-camera
Summary:    A Camera library in Tizen C API
Version:    0.2.4
Release:    0
Group:      Multimedia/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(gstreamer-1.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(mused)
BuildRequires:  pkgconfig(mm-camcorder)
BuildRequires:  pkgconfig(audio-session-mgr)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-media-tool)
%if %{with x}
BuildRequires:  pkgconfig(ecore-x)
%endif
%if %{with wayland}
BuildRequires:  pkgconfig(ecore-wayland)
%endif
BuildRequires:  pkgconfig(json)
BuildRequires:  pkgconfig(libtbm)
BuildRequires:  pkgconfig(evas)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(vconf)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig


%description
A Camera library in Tizen C API.


%package devel
Summary:  A Camera library in Tizen C API (Development)
Requires: %{name} = %{version}-%{release}
Requires: pkgconfig(libtbm)
Requires: pkgconfig(capi-media-tool)


%description devel
A Camera library in Tizen C API.

Development related files.


%prep
%setup -q


%build
%if 0%{?sec_build_binary_debug_enable}
export CFLAGS+=" -DTIZEN_DEBUG_ENABLE"
%endif
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DFULLVER=%{version} -DMAJORVER=${MAJORVER} \
%if %{with wayland}
	-DWAYLAND_SUPPORT=On \
%else
	-DWAYLAND_SUPPORT=Off \
%endif
%if %{with x}
	-DX11_SUPPORT=On
%else
	-DX11_SUPPORT=Off
%endif

make %{?jobs:-j%jobs}


%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}%{_datadir}/license
cp LICENSE.APLv2 %{buildroot}%{_datadir}/license/%{name}


%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig

%files
%manifest mmsvc-camera.manifest
%{_libdir}/libmmsvc-camera.so*
%{_libdir}/libmuse-camera.so*
%{_datadir}/license/%{name}

%files devel
%{_includedir}/media/mmsvc_camera.h
%{_includedir}/media/muse_camera.h
%{_includedir}/media/mmsvc_camera_internal.h
%{_includedir}/media/muse_camera_msg.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libmmsvc-camera.so
