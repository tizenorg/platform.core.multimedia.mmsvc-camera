Name:       capi-media-camera2
Summary:    A Camera library in Tizen C API
Version:    0.1.75
Release:    0
Group:      Multimedia/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(gstreamer-1.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(mm-camcorder)
BuildRequires:  pkgconfig(audio-session-mgr)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-media-tool)
BuildRequires:  pkgconfig(libtbm)
BuildRequires:  pkgconfig(evas)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(elementary)
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
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}


%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp LICENSE.APLv2 %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%files
%manifest capi-media-camera2.manifest
%{_libdir}/libcapi-media-camera2.so.*
%{_datadir}/license/%{name}


%files devel
%{_includedir}/media/camera2.h
%{_includedir}/media/camera2_internal.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-media-camera2.so


