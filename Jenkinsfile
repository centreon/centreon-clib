/*
** Variables.
*/
def serie = '20.10'
def maintenanceBranch = "${serie}.x"
def qaBranch = "dev-${serie}.x"

if (env.BRANCH_NAME.startsWith('release-')) {
  env.BUILD = 'RELEASE'
} else if ((env.BRANCH_NAME == 'master') || (env.BRANCH_NAME == maintenanceBranch)) {
  env.BUILD = 'REFERENCE'
} else if ((env.BRANCH_NAME == 'develop') || (env.BRANCH_NAME == qaBranch)) {
  env.BUILD = 'QA'
} else {
  env.BUILD = 'CI'
}

def checkoutCentreonBuild() {
  dir('centreon-build') {
    checkout resolveScm(source: [$class: 'GitSCMSource',
      remote: 'https://github.com/centreon/centreon-build.git',
      credentialsId: 'technique-ci',
      traits: [[$class: 'jenkins.plugins.git.traits.BranchDiscoveryTrait']]],
      targets: [BRANCH_NAME, 'master'])
  }
}

/*
** Pipeline code.
*/
stage('Source') {
  node("C++") {
    checkoutCentreonBuild()
    dir('centreon-clib') {
      checkout scm
    }
    sh "./centreon-build/jobs/clib/${serie}/mon-clib-source.sh"
    source = readProperties file: 'source.properties'
    env.VERSION = "${source.VERSION}"
    env.RELEASE = "${source.RELEASE}"
    publishHTML([
      allowMissing: false,
      keepAll: true,
      reportDir: 'summary',
      reportFiles: 'index.html',
      reportName: 'Centreon Clib Build Artifacts',
      reportTitles: ''
    ])
    withSonarQubeEnv('SonarQubeDev') {
      sh "./centreon-build/jobs/clib/${serie}/mon-clib-analysis.sh"
    }
  }
}

try {
  // sonarQube step to get qualityGate result
  stage('Quality gate') {
    node("C++") {
      timeout(time: 10, unit: 'MINUTES') {
        def qualityGate = waitForQualityGate()
        if (qualityGate.status != 'OK') {
          currentBuild.result = 'FAIL'
        }
      }
      if ((currentBuild.result ?: 'SUCCESS') != 'SUCCESS') {
        error("Quality gate failure: ${qualityGate.status}.");
      }
    }
  }

  stage('Package') {
    parallel 'packaging centos7': {
      node("C++") {
        checkoutCentreonBuild()
        sh "./centreon-build/jobs/clib/${serie}/mon-clib-package.sh centos7"
        stash name: 'el7-rpms', includes: "output/x86_64/*.rpm"
        archiveArtifacts artifacts: "output/x86_64/*.rpm"
        sh 'rm -rf output' 
      }
    },
    'packaging alma8': {
      node("C++") {
        checkoutCentreonBuild()
        sh "./centreon-build/jobs/clib/${serie}/mon-clib-package.sh alma8"
        stash name: 'alma8-rpms', includes: "output/x86_64/*.rpm"
        archiveArtifacts artifacts: "output/x86_64/*.rpm"
        sh 'rm -rf output' 
      }
    },
    'packaging debian10': {
      node("C++") {
        checkoutCentreonBuild()
        sh "./centreon-build/jobs/clib/${serie}/mon-clib-package.sh debian10"
      }
    },
    'packaging debian10-armhf': {
      node("C++") {
        checkoutCentreonBuild()
        sh "./centreon-build/jobs/clib/${serie}/mon-clib-package.sh debian10-armhf"
      }
    }
    if ((currentBuild.result ?: 'SUCCESS') != 'SUCCESS') {
      error('Packaging stage failure');
    }
  }

  if ((env.BUILD == 'RELEASE') || (env.BUILD == 'QA')) {
    stage('Delivery') {
      node("C++") {
        unstash 'el7-rpms'
        unstash 'alma8-rpms'
        checkoutCentreonBuild()
        sh "./centreon-build/jobs/clib/${serie}/mon-clib-delivery.sh"
      }
      if ((currentBuild.result ?: 'SUCCESS') != 'SUCCESS') {
        error('Delivery stage failure.');
      }
    }
  }
}
finally {
  buildStatus = currentBuild.result ?: 'SUCCESS';
  if ((buildStatus != 'SUCCESS') && ((env.BUILD == 'RELEASE') || (env.BUILD == 'REFERENCE'))) {
    slackSend channel: '#monitoring-metrology', message: "@channel Centreon Clib build ${env.BUILD_NUMBER} of branch ${env.BRANCH_NAME} was broken by ${source.COMMITTER}. Please fix it ASAP."
  }
}
